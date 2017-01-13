#ifndef ENTROPY_H
#define ENTROPY_H

#include "cooccurrencematrixbaseddescriptor.h"

class Entropy : public CooccurrenceMatrixBasedDescriptor
{
public:
    Entropy(relative_operator _operator);
    ~Entropy();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // ENTROPY_H
