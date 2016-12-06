#ifndef COOCCURRENCEMATRIXBASEDDESCRIPTOR_H
#define COOCCURRENCEMATRIXBASEDDESCRIPTOR_H

#include "../../featureextractor.h"

/*
* Point(x, y) will correspond to (row, col)
*/
typedef cv::Point (*relative_operator)(const cv::Point&);

class CooccurrenceMatrixBasedDescriptor : public FeatureExtractor
{
private:
    relative_operator _operator;

protected:
    cv::Mat calculateOccurenceMatrix(const cv::Mat& image) const;
    cv::Mat calculateProbabilityOccurenceMatrix(const cv::Mat& image) const;

public:
    /*
    * _operator: callback function to be called
    * when deciding which pixel is relative to current pixel
    * from left to right, top to bottom
    */
    CooccurrenceMatrixBasedDescriptor(relative_operator _operator);
    ~CooccurrenceMatrixBasedDescriptor() { }
};

#endif // COOCCURRENCEMATRIXBASEDDESCRIPTOR_H
