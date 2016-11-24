#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <opencv2/core/core.hpp>

#include <vector>

class FeatureExtractor
{
public:
    FeatureExtractor() {}
    virtual ~FeatureExtractor() {}

    virtual std::vector<double> extractFeature(const cv::Mat& image) const = 0;
};

#endif // FEATUREEXTRACTOR_H
