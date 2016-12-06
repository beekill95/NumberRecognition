#include "relativesmoothness.h"

std::vector<double> RelativeSmoothness::extractFeature(const cv::Mat &image) const
{
    // calculate the histogram distribution
    float histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    // calculate the mean
    double mean = histogramMean(histogramDistribution);

    // calculate the variance
    double variance = 0.0;
    for (int i = 0; i < 256; ++i) {
        double diff = mean - i;
        variance += diff * diff * histogramDistribution[i];
    }

    // normalize variance
    variance = variance / (255 * 255);

    return {1.0 - 1.0/(1 + variance)};
}

