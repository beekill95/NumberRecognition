#ifndef CONTRAST_H
#define CONTRAST_H

#include "cooccurrencematrixbaseddescriptor.h"

class Contrast : public CooccurrenceMatrixBasedDescriptor
{
public:
    Contrast(relative_operator _operator);
    ~Contrast();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // CONTRAST_H
