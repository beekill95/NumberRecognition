#ifndef COMMON
#define COMMON

#include "opencv2/core/core.hpp"

#define COARSE_IMAGE_PATH "data/images/coarse.tif"
#define SMOOTH_IMAGE_PATH "data/images/smooth.tif"
#define REGULAR_IMAGE_PATH "data/images/regular.tif"

#define RANDOM_IMAGE_PATH "data/images/random.tif"
#define PERIODIC_IMAGE_PATH "data/images/periodic.tif"
#define MIX_TEXTURE_IMAGE_PATH "data/images/mix_texture.tif"

inline cv::Point nextPixel(const cv::Point& first) {
    return cv::Point(first.x, first.y + 1);
}

#endif // COMMON

