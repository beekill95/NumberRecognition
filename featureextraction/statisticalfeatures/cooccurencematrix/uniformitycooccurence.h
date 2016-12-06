#ifndef UNIFORMITYCOOCCURENCE_H
#define UNIFORMITYCOOCCURENCE_H

#include "cooccurrencematrixbaseddescriptor.h"

class UniformityCooccurence : public CooccurrenceMatrixBasedDescriptor
{
public:
    UniformityCooccurence(relative_operator _operator);
    ~UniformityCooccurence();

    std::vector<double> extractFeature(const cv::Mat &image) const override;
};

#endif // UNIFORMITY_H
