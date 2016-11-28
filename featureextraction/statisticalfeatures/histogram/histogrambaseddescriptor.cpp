#include "histogrambaseddescriptor.h"
#include <cstring>

void HistogramBasedDescriptor::calculateHistogram(const cv::Mat &image, int histogram[])
{
    memset(histogram, 0, 256 * sizeof(int));

    for (int r = 0; r < image.rows; ++r) {
        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c)
            ++histogram[pixelRow[c]];
    }
}

void HistogramBasedDescriptor::calculateHistogram(const cv::Mat &image, float histogram[])
{
    memset(histogram, 0, 256 * sizeof(float));

    for (int r = 0; r < image.rows; ++r) {
        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c)
            ++histogram[pixelRow[c]];
    }

    int totalPixel = image.rows * image.cols;
    for (int i = 0; i < 256; ++i)
        histogram[i] /= totalPixel;
}
