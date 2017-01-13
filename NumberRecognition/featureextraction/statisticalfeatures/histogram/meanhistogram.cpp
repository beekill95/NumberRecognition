#include "meanhistogram.h"

std::vector<val_type> MeanHistogram::extractFeature(const cv::Mat &image) const
{
    // calculate histogram
    val_type histogram[256];
    calculateHistogram(image, histogram);

    // calculate mean histogram
    std::vector<val_type> mean(1);
    for (int i = 0; i < 256; ++i)
        mean[0] += i * histogram[i];

    return {mean};
}

std::vector<val_type> MeanHistogram::extractFeature(const val_type *histogram) const
{
    // calculate mean histogram
    std::vector<val_type> mean(1);
    for (int i = 0; i < 256; ++i)
        mean[0] += i * histogram[i];

    return {mean};
}
