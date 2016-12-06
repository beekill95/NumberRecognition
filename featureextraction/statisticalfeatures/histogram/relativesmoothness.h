#ifndef RELATIVESMOOTHNESS_H
#define RELATIVESMOOTHNESS_H

#include "histogrambaseddescriptor.h"

class RelativeSmoothness : public HistogramBasedDescriptor
{
public:
    RelativeSmoothness() { }
    ~RelativeSmoothness() { }

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // RELATIVESMOOTHNESS_H
