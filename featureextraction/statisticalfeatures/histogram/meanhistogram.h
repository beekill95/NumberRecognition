#ifndef MEANHISTOGRAM_H
#define MEANHISTOGRAM_H

#include "histogrambaseddescriptor.h"

class MeanHistogram : public HistogramBasedDescriptor
{
public:
    MeanHistogram() { }
    ~MeanHistogram() { }

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // MEANHISTOGRAM_H
