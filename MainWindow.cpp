#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QImageReader>

#include "Hashes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    for (int i = 0; i < hashes.size(); i++)
        delete hashes.at(i);
}

void MainWindow::setupResultTable()
{
    QTableWidget *table = ui->resultTable;

    table->setRowCount(0);

    table->setColumnCount(3);

    table->setColumnWidth(0, 300);
    table->setColumnWidth(1, 300);
    table->setColumnWidth(2, 60);

    QStringList headers;
    headers << "File 1" << "File 2" << "Match, %";
    table->setHorizontalHeaderLabels(headers);
}

void MainWindow::startScanDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select directory"));

    if (!dir.isNull()) {
        // Clear old hashes
        for (int i = 0; i < hashes.size(); i++)
            delete hashes.at(i);
        hashes.clear();

        setupResultTable();


        if (ui->cbAlgorithm->currentIndex() == 0)
            hashFunc = &Hashes::getImageAHash;
        else if (ui->cbAlgorithm->currentIndex() == 1)
            hashFunc = &Hashes::getImagePHash;
        else if (ui->cbAlgorithm->currentIndex() == 2)
            hashFunc = &Hashes::getImageDHash;

        aborted = false;
        ui->btnAbort->setEnabled(true);

        totalFiles = 0;
        readDirHashes(dir);

        // Search duplicates
        ui->infoLabel->setText(QString(tr("Start search dublicates...")));
        QApplication::processEvents();

        int threshold = 256 - ui->tbMatch->value() * 2.56;

        for (int i = 0; i < hashes.size() - 1; i++)
        {
            for (int j = i + 1; j < hashes.size(); j++)
            {
                short distance = Utils::HammingDist(hashes.at(i), hashes.at(j));
                if (distance <= threshold)
                {
                    ui->resultTable->insertRow(0);
                    addTableResultItem(0, hashes.at(i)->getFileName());
                    addTableResultItem(1, hashes.at(j)->getFileName());
                    addTableResultItem(2, QString("%0 \%").arg(QString::number(100 - distance * 100 / 256)));
                }
            }
        }
        ui->infoLabel->setText(QString(tr("Finished. Total %0 files scanned")).arg(totalFiles));

        QMessageBox::information(this, tr("Information"), tr("Finished"), QMessageBox::Ok);
    }
}

void MainWindow::addTableResultItem(const int column, const QString text)
{
    ui->resultTable->setItem(0, column, new QTableWidgetItem(text));
}

void MainWindow::readDirHashes(QString path)
{
    // Read directory
    QDir dir(path);

    QFileInfoList files = dir.entryInfoList(QDir::AllEntries | QDir::Readable | QDir::NoDotAndDotDot);

    foreach (const QFileInfo &fi, files)
    {
        if (aborted)
            break;

        QString fileName = fi.absoluteFilePath();

        if (fi.isDir() && fi.fileName() != "Best")
        {
            readDirHashes(fileName);
        }
        else
        {
            UpdateStatusInfo(path);

            QByteArray extension;
            extension.append(fi.suffix().toLower());

            if (QImageReader::supportedImageFormats().indexOf(extension) != -1)
            {
                CImageHashInfo *hash = hashFunc(fileName);

                if (hash != NULL)
                    hashes.push_back(hash);
            }
        }
    }
}

void MainWindow::UpdateStatusInfo(QString currentFile)
{
    if (++totalFiles % 10 == 0)
    {
        ui->infoLabel->setText(QString(tr("Scan file #%0 (%1)")).arg(totalFiles).arg(currentFile));
        QApplication::processEvents();
    }
}

void MainWindow::on_resultTable_itemSelectionChanged()
{
    int currentRow = ui->resultTable->currentRow();

    if (currentRow != -1)
    {
        displayImageInfo(ui->resultTable->item(currentRow, 0)->text(), ui->lbFileName1, ui->lbImageSize1, ui->lbImage1);
        displayImageInfo(ui->resultTable->item(currentRow, 1)->text(), ui->lbFileName2, ui->lbImageSize2, ui->lbImage2);
    }
}

void MainWindow::displayImageInfo(QString filePath, QLabel* lbFileName, QLabel* lbSize, QLabel* lbImage)
{
    lbFileName->setText(filePath);

    if (QFile::exists(filePath))
    {
        QImage image(filePath);
        lbSize->setText(QString("%1x%2").arg(image.size().width()).arg(image.size().height()));

        QImage thumb = image.scaled(QSize(250, 250), Qt::KeepAspectRatio);
        lbImage->setFixedSize(thumb.size());
        lbImage->setPixmap(QPixmap::fromImage(thumb));
    } else {
        lbSize->clear();
        lbImage->clear();
    }
}

void MainWindow::openShell(const QString &pathIn)
{
#if defined(Q_OS_WIN)
    QString param;
    if (!QFileInfo(pathIn).isDir())
        param = QLatin1String("/select,");
    param += QDir::toNativeSeparators(pathIn);

    QProcess::startDetached("explorer.exe " + param);
#else
    const QFileInfo fileInfo(pathIn);
    const QString folder = fileInfo.absoluteFilePath();
    const QString app = Utils::UnixUtils::fileBrowser(Core::ICore::instance()->settings());
    QProcess browserProc;
    const QString browserArgs = Utils::UnixUtils::substituteFileBrowserParameters(app, folder);
    if (debug)
        qDebug() <<  browserArgs;
    bool success = browserProc.startDetached(browserArgs);
    const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
    success = success && error.isEmpty();
    if (!success)
        showGraphicalShellError(parent, app, error);
#endif
}

void MainWindow::on_pushButton_clicked()
{
    openShell(ui->lbFileName1->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    openShell(ui->lbFileName2->text());
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_btnAbort_clicked()
{
    aborted = true;
    ui->btnAbort->setEnabled(false);
}

void MainWindow::removeFromList(QString fileName)
{
    if (QMessageBox::question(this, "Delete file", "Delete file \"" + fileName + "\"?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        QFile::remove(fileName);

        int currentRow = ui->resultTable->currentRow();
        ui->resultTable->removeRow(currentRow);

        // Search and remove all entrys with deleted file
        for (int i = 0; i < ui->resultTable->rowCount(); i++)
        {
            if (ui->resultTable->item(i, 0)->text() == fileName ||
                ui->resultTable->item(i, 1)->text() == fileName)
            {
                ui->resultTable->removeRow(i);
                i--;
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    removeFromList(ui->lbFileName1->text());
}

void MainWindow::on_pushButton_4_clicked()
{
    removeFromList(ui->lbFileName2->text());
}
