#include "averageentropy.h"

#include <cmath>

std::vector<double> AverageEntropy::extractFeature(const cv::Mat &image) const
{
    float histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    double entropy = 0.0;
    for (int i = 0; i < 256; ++i)
        if (histogramDistribution[i] != 0.0f)
            entropy += histogramDistribution[i] * log2(histogramDistribution[i]);

    return {-entropy};
}

