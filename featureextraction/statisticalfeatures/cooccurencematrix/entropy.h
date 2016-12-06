#ifndef ENTROPY_H
#define ENTROPY_H

#include "cooccurrencematrixbaseddescriptor.h"

class Entropy : public CooccurrenceMatrixBasedDescriptor
{
public:
    Entropy(relative_operator _operator);
    ~Entropy();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // ENTROPY_H
