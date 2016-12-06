#ifndef AVERAGEENTROPY_H
#define AVERAGEENTROPY_H

#include "histogrambaseddescriptor.h"

class AverageEntropy : public HistogramBasedDescriptor
{
public:
    AverageEntropy() { }
    ~AverageEntropy() { }

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // AVERAGEENTROPY_H
