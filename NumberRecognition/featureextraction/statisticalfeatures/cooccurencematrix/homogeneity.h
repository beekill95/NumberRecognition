#ifndef HOMOGENEITY_H
#define HOMOGENEITY_H

#include "cooccurrencematrixbaseddescriptor.h"

class Homogeneity : public CooccurrenceMatrixBasedDescriptor
{
public:
    Homogeneity(relative_operator _operator);
    ~Homogeneity();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // HOMOGENEITY_H
