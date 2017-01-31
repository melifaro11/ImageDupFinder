#include "ImageHashInfo.h"

/**
 * @brief CImageHashInfo Create new CImageHashInfo object
 * @param path Path to image
 */
CImageHashInfo::CImageHashInfo(const QString path): filePath(path)
{
    hashValue.reserve(16);
}

/**
 * @brief Destroy CImageHashInfo object
 */
CImageHashInfo::~CImageHashInfo(void)
{
}

/**
 * @brief appendToHash Append next part of a hash to general
 * @param hashPart Part of a hash (one line)
 */
void CImageHashInfo::appendToHash(const ushort hashPart)
{
    hashValue.push_back(hashPart);
}

/**
 * @brief getHashPart Returns part of a hash at given index
 * @param index Index of a part
 * @return Hash part
 */
ushort CImageHashInfo::getHashPart(const int index) const
{
    if (index < hashValue.size())
        return hashValue.at(index);
    else
        return 0;
}

/**
 * @brief getFileName Returns associated file name
 * @return associated file name
 */
QString CImageHashInfo::getFileName() const
{
    return filePath;
}
