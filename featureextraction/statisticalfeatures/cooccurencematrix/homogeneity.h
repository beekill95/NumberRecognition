#ifndef HOMOGENEITY_H
#define HOMOGENEITY_H

#include "cooccurrencematrixbaseddescriptor.h"

class Homogeneity : public CooccurrenceMatrixBasedDescriptor
{
public:
    Homogeneity(relative_operator _operator);
    ~Homogeneity();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // HOMOGENEITY_H
