/**
 * Copyright 2016-2017 Alexandr Mitiaev
 *
 * This file is part of ImgDupFinder.
 *
 * ImgDupFinder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImgDupFinder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImgDupFinder. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "ImageHashInfo.h"
#include "Utils.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Create window
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Destroy window
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * @brief hashes List of all hashes
     */
    QVector<CImageHashInfo*> hashes;

    /**
     * @brief Pointer type to hash-function
     */
    typedef CImageHashInfo*(*pfImageHash)(const QString);

    /**
     * @brief hashFunc Pointer to current hash-function
     */
    pfImageHash hashFunc;

    /**
     * @brief totalFiles Number of processed files
     */
    ulong totalFiles;

    /**
     * @brief aborted Process was aborted
     */
    bool aborted;

    /**
     * @brief Mainwindow::readDirHashes - Scan recursive a given directory
     * @param path Start path
     */
    void readDirHashes(QString path);

    /**
     * @brief openShell Open given file in explorer
     * @param pathIn Path to a file
     */
    void openShell(const QString &pathIn);

    /**
     * @brief MainWindow::addTableResultItem Append text to 0 row of result table
     * @param column Column to add item
     * @param text Text to add
     */
    void addTableResultItem(const int column, const QString text);

    /**
     * @brief MainWindow::displayImageInfo Display information about a file on a given widgets
     * @param filePath Path to image file
     * @param lbFileName Widget to display name of file
     * @param lbSize Widget to display image size
     * @param lbImage Widget to display image
     */
    void displayImageInfo(QString filePath, QLabel* lbFileName, QLabel* lbSize, QLabel* lbImage);

    /**
     * @brief setupResultTable Reset result table and set up columns
     */
    void setupResultTable();

    /**
     * @brief MainWindow::UpdateStatusInfo Update file information on status text
     * @param currentFile
     */
    void UpdateStatusInfo(QString currentFile);

    /**
     * @brief removeFromList Remove file from disk and result list
     * @param fileName Name of a file
     */
    void removeFromList(QString fileName);

public slots:
    /**
     * @brief startScanDirectory
     * @remarks Start scan directory to find duplicates
     */
    void startScanDirectory();
private slots:
    /**
     * @brief on_pushButton_clicked Open file 1 in browser
     */
    void on_pushButton_clicked();

    /**
     * @brief on_pushButton_2_clicked Open file 2 in browser
     */
    void on_pushButton_2_clicked();

    /**
     * @brief on_resultTable_itemSelectionChanged Select result string
     */
    void on_resultTable_itemSelectionChanged();
    void on_action_Exit_triggered();
    void on_btnAbort_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
