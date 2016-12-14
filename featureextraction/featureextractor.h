#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include "definition.h"

#include <opencv2/core/core.hpp>
#include <vector>

class FeatureExtractor
{
public:
    FeatureExtractor() {}
    virtual ~FeatureExtractor() {}

    virtual std::vector<val_type> extractFeature(const cv::Mat& image) const = 0;
    virtual int getFeatureCount() const = 0;
};

#endif // FEATUREEXTRACTOR_H
