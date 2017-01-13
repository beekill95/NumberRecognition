#ifndef CORRELATION_H
#define CORRELATION_H

#include "cooccurrencematrixbaseddescriptor.h"

class Correlation : public CooccurrenceMatrixBasedDescriptor
{
public:
    Correlation(relative_operator _operator);
    ~Correlation();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurMatrix) const override;
    int getFeatureCount() const override {return 1;}
};

#endif // CORRELATION_H
