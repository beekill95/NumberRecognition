#ifndef RELATIVESMOOTHNESS_H
#define RELATIVESMOOTHNESS_H

#include "histogrambaseddescriptor.h"

class RelativeSmoothness : public HistogramBasedDescriptor
{
public:
    RelativeSmoothness() { }
    ~RelativeSmoothness() { }

    int getFeatureCount() const override {return 1;}
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    std::vector<val_type> extractFeature(const val_type* histogram) const override;
};

#endif // RELATIVESMOOTHNESS_H
