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
