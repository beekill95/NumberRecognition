#ifndef UNIFORMITYCOOCCURENCE_H
#define UNIFORMITYCOOCCURENCE_H

#include "cooccurrencematrixbaseddescriptor.h"

class UniformityCooccurence : public CooccurrenceMatrixBasedDescriptor
{
public:
    UniformityCooccurence(relative_operator _operator);
    ~UniformityCooccurence();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // UNIFORMITY_H
