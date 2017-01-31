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
