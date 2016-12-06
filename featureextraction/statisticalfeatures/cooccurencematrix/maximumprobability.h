#ifndef MAXIMUMPROBABILITY_H
#define MAXIMUMPROBABILITY_H

#include "cooccurrencematrixbaseddescriptor.h"

class MaximumProbability : public CooccurrenceMatrixBasedDescriptor
{
public:
    MaximumProbability(relative_operator _operator);
    ~MaximumProbability();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // MAXIMUMPROBABILITY_H
