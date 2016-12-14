#include "averageentropy.h"

#include <cmath>

std::vector<val_type> AverageEntropy::extractFeature(const cv::Mat &image) const
{
    val_type histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    val_type entropy = 0.0;
    for (int i = 0; i < 256; ++i)
        if (histogramDistribution[i] != 0.0f)
            entropy += histogramDistribution[i] * log2(histogramDistribution[i]);

    return {-entropy};
}

std::vector<val_type> AverageEntropy::extractFeature(const val_type *histogram) const
{
    val_type entropy = 0.0;
    for (int i = 0; i < 256; ++i)
        if (histogram[i] != 0.0f)
            entropy += histogram[i] * log2(histogram[i]);

    return {-entropy};
}
