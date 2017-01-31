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

#include "Utils.h"

#define _USE_MATH_DEFINES

#include <math.h>

/**
 * @brief AHASH_BLOCK Size of the block for aHash-algorithm
 */
const QSize Utils::AHASH_BLOCK = QSize(16, 16);

/**
 * @brief PHASH_BLOCK Size of the block for pHash-algorithm
 */
const QSize Utils::PHASH_BLOCK = QSize(DCT_BLOCK_SIZE, DCT_BLOCK_SIZE);

/**
 * @brief PHASH_BLOCK Size of the block for dHash-algorithm
 */
const QSize Utils::DHASH_BLOCK = QSize(9, 8);

/**
 * @brief Utils::Utils
 */
Utils::Utils()
{
}

/**
 * @brief HammingDist Calculate Hamming distance between two short integers
 * @param x first digit
 * @param y second digit
 * @return Hamming distance
 */
short Utils::HammingDist(ushort x, ushort y)
{
    short dist = 0;
    ushort val = x ^ y;

    while (val)
    {
        ++dist;
        val &= val - 1;
    }

    return dist;
}

/**
 * @brief getHammingDist Returns Hamming distance between given CImageHashInfo-hashes
 * @param hash1 First hash info
 * @param hash2 Second hash info
 * @return Hamming distance between given hashes
 */
short Utils::HammingDist(CImageHashInfo* hash1, CImageHashInfo* hash2)
{
    short distance = 0;

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        distance += HammingDist(hash1->getHashPart(i), hash2->getHashPart(i));
    }

    return distance;
}

/**
 * @brief getGrayValue Return gray value from rgb-value
 * @param aRgb aRgb in form 0xffRRGGBB
 * @return gray level
 */
unsigned char Utils::getGrayValue(const QRgb aRgb)
{
    return ((aRgb & 0xFF) + ((aRgb & 0xFF00) >> 8) + ((aRgb & 0xFF0000) >> 16)) / 3;
}

/**
 * @brief lyambda Lyambda-value for DCT-Transform
 */
const double Utils::LYAMBDA = 1 / sqrt(2.0);

/**
 * @brief DCT Perform DCT-Transform with a given matrix (DCT_BLOCK_SIZE x DCT_BLOCK_SIZE)
 * @param matrix Input matrix
 * @return DCT-matrix as a vector with length DCT_BLOCK_SIZE x DCT_BLOCK_SIZE
 */
short* Utils::DCT(uchar matrix[DCT_BLOCK_SIZE][DCT_BLOCK_SIZE])
{
    short *resultMatrix = new short[DCT_BLOCK_SIZE * DCT_BLOCK_SIZE];

    for (int u = 0; u < DCT_BLOCK_SIZE; u++)
    {
        for (int v = 0; v < DCT_BLOCK_SIZE; v++)
        {
            double result = 0;
            for (int i = 0; i < DCT_BLOCK_SIZE; i++)
            {
                for (int j = 0; j < DCT_BLOCK_SIZE; j++)
                {
                    double x = i ? 1 : LYAMBDA;
                    double y = j ? 0 : LYAMBDA;

                    result += (x * y * cos(((M_PI * u) / DCT_BLOCK_SIZE_DUP) * (2 * i + 1)) *
                                       cos(((M_PI * v) / DCT_BLOCK_SIZE_DUP) * (2 * j + 1)) *
                                       matrix[i][j]);
                }
            }

            resultMatrix[u * DCT_BLOCK_SIZE + v] = result;
        }
    }

    return resultMatrix;
}
