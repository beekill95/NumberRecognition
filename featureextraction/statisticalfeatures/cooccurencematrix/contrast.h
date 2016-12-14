#ifndef CONTRAST_H
#define CONTRAST_H

#include "cooccurrencematrixbaseddescriptor.h"

class Contrast : public CooccurrenceMatrixBasedDescriptor
{
public:
    Contrast(relative_operator _operator);
    ~Contrast();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // CONTRAST_H
