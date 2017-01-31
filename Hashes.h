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

#ifndef HASHES_H
#define HASHES_H

#include "ImageHashInfo.h"

class Hashes
{
public:
    Hashes();

    /**
     * @brief Calculate aHash for an image
     * @param path Path to image file
     * @return Image aHash-value
     */
    static CImageHashInfo* getImageAHash(const QString path);

    /**
     * @brief Calculate pHash for an image
     * @param path Path to image file
     * @return Image pHash-value
     */
    static CImageHashInfo* getImagePHash(const QString path);

    /**
     * @brief Calculate pHash for an image
     * @param path Path to image file
     * @return Image pHash-value
     */
    static CImageHashInfo* getImageDHash(const QString path);
};

#endif // HASHES_H
