#ifndef UNIFORMITY_H
#define UNIFORMITY_H

#include "histogrambaseddescriptor.h"

class UniformityHistogram : public HistogramBasedDescriptor
{
public:
    UniformityHistogram() { }
    ~UniformityHistogram() { }

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // UNIFORMITY_H
