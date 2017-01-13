#ifndef MAXIMUMPROBABILITY_H
#define MAXIMUMPROBABILITY_H

#include "cooccurrencematrixbaseddescriptor.h"

class MaximumProbability : public CooccurrenceMatrixBasedDescriptor
{
public:
    MaximumProbability(relative_operator _operator);
    ~MaximumProbability();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // MAXIMUMPROBABILITY_H
