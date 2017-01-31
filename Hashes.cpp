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

#include "Hashes.h"

#include <QImageReader>
#include <QImage>

#include "Utils.h"

Hashes::Hashes()
{
}

/**
 * @brief Calculate pHash for a given image
 *
 * @param path Path to the image
 *
 * @return pHash of the image
 */
CImageHashInfo* Hashes::getImagePHash(const QString path)
{
    QImageReader reader(path);

    reader.setScaledSize(Utils::PHASH_BLOCK);

    if (reader.canRead())
    {
        // Read and convert into RGB-Format (0xffRRGGBB, if need)
        QImage image = reader.read().scaled(Utils::PHASH_BLOCK);

        if (image.format() != QImage::Format_RGB32)
            image = image.convertToFormat(QImage::Format_RGB32);

        // Convert image to grayscale
        uchar imageMatrix[Utils::DCT_BLOCK_SIZE][Utils::DCT_BLOCK_SIZE];

        for (int i = 0; i < Utils::DCT_BLOCK_SIZE; i++)
        {
            QRgb* line = (QRgb*)image.scanLine(i);

            for (int j = 0; j < Utils::DCT_BLOCK_SIZE; j++)
            {
                imageMatrix[i][j] = Utils::getGrayValue(line[j]);
            }
        }

        // Start DCT-Transform
        short *resultMatrix = Utils::DCT(imageMatrix);

        // Reduce DCT-Matrix and calculate average value
        short reducedMatrix[Utils::AHASH_BLOCK.height()][Utils::AHASH_BLOCK.width()];
        int sum = 0;
        for (int i = 0; i < Utils::AHASH_BLOCK.height(); i++)
        {
            for (int j = 0; j < Utils::AHASH_BLOCK.width(); j++)
            {
                if (i || j) {
                    reducedMatrix[i][j] = resultMatrix[i * Utils::PHASH_BLOCK.width() + j];
                    sum += reducedMatrix[i][j];
                }
            }
        }
        int average = sum / (Utils::AHASH_BLOCK.width() * Utils::AHASH_BLOCK.height());

        delete resultMatrix;

        // Calculate hash value of a image
        CImageHashInfo *hashInfo = new CImageHashInfo(path);

        for (int i = 0; i < Utils::AHASH_BLOCK.height(); i++)
        {
            ushort lineHash = 0;
            for (int j = 0; j < Utils::AHASH_BLOCK.width(); j++)
            {
                if (imageMatrix[i][j] >= average)
                    lineHash |= 1 << j;
            }

            hashInfo->appendToHash(lineHash);
        }

        return hashInfo;
    }

    return NULL;
}

/**
 * @brief Calculate aHash for a given image
 *
 * @param path Path to the image
 *
 * @return aHash of the image
 */
CImageHashInfo* Hashes::getImageAHash(const QString path)
{
    QImageReader reader(path);

    reader.setScaledSize(Utils::AHASH_BLOCK);

    if (reader.canRead())
    {
        // Read and convert into RGB-Format (0xffRRGGBB, if need)
        QImage image = reader.read().scaled(Utils::AHASH_BLOCK);

        if (image.format() != QImage::Format_RGB32)
            image = image.convertToFormat(QImage::Format_RGB32);

        // Convert image to grayscale and calculate average value
        ulong sum = 0;
        uchar imageMatrix[Utils::AHASH_BLOCK.height()][Utils::AHASH_BLOCK.width()];
        for (int i = 0; i < Utils::AHASH_BLOCK.height(); i++)
        {
            QRgb* line = (QRgb*)image.scanLine(i);

            for (int j = 0; j < Utils::AHASH_BLOCK.width(); j++)
            {
                imageMatrix[i][j] = Utils::getGrayValue(line[j]);
                sum += imageMatrix[i][j];
            }
        }

        int average = sum / (Utils::AHASH_BLOCK.width() * Utils::AHASH_BLOCK.height());

        // Calculate hash value of a image
        CImageHashInfo *hashInfo = new CImageHashInfo(path);

        for (int i = 0; i < Utils::AHASH_BLOCK.height(); i++)
        {
            ushort lineHash = 0;
            for (int j = 0; j < Utils::AHASH_BLOCK.width(); j++)
            {
                if (imageMatrix[i][j] >= average)
                    lineHash |= 1 << j;
            }

            hashInfo->appendToHash(lineHash);
        }

        return hashInfo;
    }

    return NULL;
}

/**
 * @brief Calculate dHash for a given image
 *
 * @param path Path to the image
 *
 * @return dHash of the image
 */
CImageHashInfo* Hashes::getImageDHash(const QString path)
{
    QImageReader reader(path);

    reader.setScaledSize(Utils::DHASH_BLOCK);

    if (reader.canRead())
    {
        // Read and convert into RGB-Format (0xffRRGGBB, if need)
        QImage image = reader.read().scaled(Utils::DHASH_BLOCK);

        if (image.format() != QImage::Format_RGB32)
            image = image.convertToFormat(QImage::Format_RGB32);

        // Convert image to grayscale
        uchar grayscaleImage[Utils::DHASH_BLOCK.height()][Utils::DHASH_BLOCK.width()];

        for (int i = 0; i < Utils::DHASH_BLOCK.height(); i++)
        {
            QRgb* line = (QRgb*)image.scanLine(i);

            for (int j = 0; j < Utils::DHASH_BLOCK.width(); j++)
            {
                grayscaleImage[i][j] = Utils::getGrayValue(line[j]);
            }
        }

        // Calculate hash value of a image
        CImageHashInfo *hashInfo = new CImageHashInfo(path);

        for (int i = 0; i < Utils::DHASH_BLOCK.height(); i++)
        {
            ushort lineHash = 0;
            for (int j = 0; j < Utils::DHASH_BLOCK.width() - 1; j++)
            {
                if (grayscaleImage[i][j] < grayscaleImage[i][j + 1])
                    lineHash |= 1 << j;
            }

            hashInfo->appendToHash(lineHash);
        }

        return hashInfo;
    }

    return NULL;
}
