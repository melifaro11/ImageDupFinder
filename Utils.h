#ifndef UTILS_H
#define UTILS_H

#include <QRgb>
#include <QSize>

#include "ImageHashInfo.h"

class Utils
{
public:
    /**
     * @brief Utils
     */
    Utils();

    /**
     * @brief lyambda Lyambda-value for DCT-Transform
     */
    static const double LYAMBDA;

    /**
     * @brief AHASH_BLOCK Size of the block for aHash-algorithm
     */
    static const QSize AHASH_BLOCK;

    /**
     * @brief PHASH_BLOCK Size of the block for pHash-algorithm
     */
    static const QSize PHASH_BLOCK;

    /**
     * @brief PHASH_BLOCK Size of the block for dHash-algorithm
     */
    static const QSize DHASH_BLOCK;

    /**
     * @brief BLOCK_SIZE Hash block size
     */
    static const int BLOCK_SIZE = 16;

    /**
     * @brief DCT_BLOCK_SIZE DCT-block size
     */
    static const int DCT_BLOCK_SIZE = 32;

    /**
     * @brief DCT_BLOCK_SIZE * 2
     */
    static const int DCT_BLOCK_SIZE_DUP = DCT_BLOCK_SIZE * 2;

    /**
     * @brief getGrayValue Return gray value from rgb-value
     * @param aRgb aRgb in form 0xffRRGGBB
     * @return gray level
     */
    static unsigned char getGrayValue(const QRgb aRgb);

    /**
     * @brief HammingDist Calculate Hamming distance between two short integers
     * @param x first digit
     * @param y second digit
     * @return Hamming distance
     */
    static short HammingDist(const ushort x, const ushort y);

    /**
     * @brief getHammingDist Returns Hamming distance between given CImageHashInfo-hashes
     * @param hash1 First hash info
     * @param hash2 Second hash info
     * @return Hamming distance between given hashes
     */
    static short HammingDist(CImageHashInfo* hash1, CImageHashInfo* hash2);

    /**
     * @brief DCT Perform DCT-Transform with a given matrix (DCT_BLOCK_SIZE x DCT_BLOCK_SIZE)
     * @param matrix Input matrix
     * @return DCT-matrix as a vector with length DCT_BLOCK_SIZE x DCT_BLOCK_SIZE
     */
    static short* DCT(uchar matrix[DCT_BLOCK_SIZE][DCT_BLOCK_SIZE]);
};

#endif // UTILS_H
