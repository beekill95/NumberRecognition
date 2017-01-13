#include "relativesmoothness.h"

std::vector<val_type> RelativeSmoothness::extractFeature(const cv::Mat &image) const
{
    // calculate the histogram distribution
    val_type histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    // calculate the mean
    val_type mean = meanHistogram(histogramDistribution);

    // calculate the variance
    val_type variance = 0.0;
    for (int i = 0; i < 256; ++i) {
        val_type diff = mean - i;
        variance += diff * diff * histogramDistribution[i];
    }

    // normalize variance
    variance /= (255 * 255);

    return {1.0 - 1.0/(1 + variance)};
}

std::vector<val_type> RelativeSmoothness::extractFeature(const val_type *histogram) const
{
    // calculate the mean
    val_type mean = meanHistogram(histogram);

    // calculate the variance
    val_type variance = 0.0;
    for (int i = 0; i < 256; ++i) {
        val_type diff = mean - i;
        variance += diff * diff * histogram[i];
    }

    // normalize variance
    variance /= (255 * 255);

    return {1.0 - 1.0/(1 + variance)};
}
