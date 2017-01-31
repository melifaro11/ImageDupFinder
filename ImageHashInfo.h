#ifndef IMAGEHASHINFO_H
#define IMAGEHASHINFO_H

#include<QString>
#include<QVector>

class CImageHashInfo
{
public:
    /**
     * @brief CImageHashInfo Create new CImageHashInfo object
     * @param path Path to image
     */
    CImageHashInfo(const QString path);

    /**
     * @brief Destroy CImageHashInfo object
     */
    ~CImageHashInfo(void);

    /**
     * @brief appendToHash Append next part of a hash to general
     * @param hashPart Part of a hash (one line)
     */
    void appendToHash(const ushort hashPart);

    /**
     * @brief getHashPart Returns part of a hash at given index
     * @param index Index of a part
     * @return Hash part
     */
    ushort getHashPart(const int index) const;

    /**
     * @brief getFileName Returns associated file name
     * @return associated file name
     */
    QString getFileName() const;

private:
    /**
     * @brief filePath Path to file
     */
    QString filePath;

    /**
     * @brief hashValue Image hash value
     */
    QVector<unsigned short> hashValue;
};

#endif // IMAGEHASHINFO_H
