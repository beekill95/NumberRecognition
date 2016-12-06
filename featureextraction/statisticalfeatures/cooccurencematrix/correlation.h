#ifndef CORRELATION_H
#define CORRELATION_H

#include "cooccurrencematrixbaseddescriptor.h"

class Correlation : public CooccurrenceMatrixBasedDescriptor
{
public:
    Correlation(relative_operator _operator);
    ~Correlation();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // CORRELATION_H
