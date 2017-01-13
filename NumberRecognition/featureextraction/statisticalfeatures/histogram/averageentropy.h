#ifndef AVERAGEENTROPY_H
#define AVERAGEENTROPY_H

#include "histogrambaseddescriptor.h"

class AverageEntropy : public HistogramBasedDescriptor
{
public:
    AverageEntropy() { }
    ~AverageEntropy() { }

    int getFeatureCount() const override {return 1;}
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    std::vector<val_type> extractFeature(const val_type* histogram) const override;
};

#endif // AVERAGEENTROPY_H
