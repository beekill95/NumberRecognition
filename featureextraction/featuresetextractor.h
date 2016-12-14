#ifndef FEATURESETEXTRACTOR_H
#define FEATURESETEXTRACTOR_H

#include "featureextractor.h"

#include <opencv2/core/core.hpp>
#include <vector>

class FeatureSetExtractor : public FeatureExtractor
{
protected:
    std::vector<FeatureExtractor* > featureExtractors;

public:
    FeatureSetExtractor();
    //FeatureSetExtractor(const std::vector<FeatureExtractor*>& featureExtractors);
    FeatureSetExtractor(std::vector<FeatureExtractor *>&& featureExtractors);
    virtual ~FeatureSetExtractor();

    virtual void addFeature(FeatureExtractor* featureExtractor);
    int getFeatureCount() const override;

    virtual std::vector<val_type> extractFeature(const cv::Mat& image) const;
//    std::vector<std::vector<val_type> > batchExtractFeatures(const std::vector<cv::Mat>& images) const;
};

#endif // FEATURESETEXTRACTOR_H
