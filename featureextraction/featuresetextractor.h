#ifndef FEATURESETEXTRACTOR_H
#define FEATURESETEXTRACTOR_H

#include "featureextractor.h"

#include <opencv2/core/core.hpp>
#include <vector>

class FeatureSetExtractor
{
private:
    std::vector<FeatureExtractor* > featureExtractors;

public:
    FeatureSetExtractor();
    //FeatureSetExtractor(const std::vector<FeatureExtractor*>& featureExtractors);
    FeatureSetExtractor(std::vector<FeatureExtractor *>&& featureExtractors);
    ~FeatureSetExtractor();

    void addFeature(FeatureExtractor* featureExtractor);

    std::vector<double> extractFeatures(const cv::Mat& image) const;
    std::vector<std::vector<double> > batchExtractFeatures(const std::vector<cv::Mat>& images) const;
};

#endif // FEATURESETEXTRACTOR_H
