#include "pixelextractor.h"

PixelExtractor::PixelExtractor()
{ }

PixelExtractor::~PixelExtractor()
{ }

std::vector<double> PixelExtractor::extractFeature(const cv::Mat &image) const
{
    std::vector<double> pixels(image.rows * image.cols);

    for (int r = 0; r < image.rows; ++r) {
        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c)
            pixels[r * image.cols + c] = pixelRow[c];
    }

    return pixels;
}
