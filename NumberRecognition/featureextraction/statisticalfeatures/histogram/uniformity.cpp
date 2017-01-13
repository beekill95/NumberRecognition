#include "uniformity.h"

std::vector<val_type> UniformityHistogram::extractFeature(const cv::Mat &image) const
{
    val_type histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    val_type uniformity = 0.0;
    for (int i = 0; i< 256; ++i)
        uniformity += histogramDistribution[i] * histogramDistribution[i];

    return {uniformity};
}

std::vector<val_type> UniformityHistogram::extractFeature(const val_type *histogram) const
{
    val_type uniformity = 0.0;
    for (int i = 0; i< 256; ++i)
        uniformity += histogram[i] * histogram[i];

    return {uniformity};
}
