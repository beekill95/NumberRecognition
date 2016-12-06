#include "meanhistogram.h"

std::vector<double> MeanHistogram::extractFeature(const cv::Mat &image) const
{
    // calculate histogram
    float histogram[256];
    calculateHistogram(image, histogram);

    // calculate mean histogram
    std::vector<double> mean(1);
    for (int i = 0; i < 256; ++i)
        mean[0] += i * histogram[i];

    return {mean};
}

