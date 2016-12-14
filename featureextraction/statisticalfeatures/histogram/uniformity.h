#ifndef UNIFORMITY_H
#define UNIFORMITY_H

#include "histogrambaseddescriptor.h"

class UniformityHistogram : public HistogramBasedDescriptor
{
public:
    UniformityHistogram() { }
    ~UniformityHistogram() { }

    int getFeatureCount() const override {return 1;}
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    std::vector<val_type> extractFeature(const val_type* histogram) const override;
};

#endif // UNIFORMITY_H
