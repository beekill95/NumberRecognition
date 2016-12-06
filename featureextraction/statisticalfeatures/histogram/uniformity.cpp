#include "uniformity.h"

std::vector<double> UniformityHistogram::extractFeature(const cv::Mat &image) const
{
    float histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    double uniformity = 0.0;
    for (int i = 0; i< 256; ++i)
        uniformity += histogramDistribution[i] * histogramDistribution[i];

    return {uniformity};
}

