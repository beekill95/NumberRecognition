#ifndef MEANHISTOGRAM_H
#define MEANHISTOGRAM_H

#include "histogrambaseddescriptor.h"

class MeanHistogram : public HistogramBasedDescriptor
{
public:
    MeanHistogram() { }
    ~MeanHistogram() { }

    int getFeatureCount() const override {return 1;}
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    std::vector<val_type> extractFeature(const val_type* histogram) const override;
};

#endif // MEANHISTOGRAM_H
