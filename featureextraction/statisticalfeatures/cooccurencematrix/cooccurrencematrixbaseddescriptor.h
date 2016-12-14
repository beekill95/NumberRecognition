#ifndef COOCCURRENCEMATRIXBASEDDESCRIPTOR_H
#define COOCCURRENCEMATRIXBASEDDESCRIPTOR_H

#include "../../featuresetextractor.h"

/*
* Point(x, y) will correspond to (row, col)
*/
typedef cv::Point (*relative_operator)(const cv::Point&);

class CooccurrenceMatrixBasedFeatureSet : public FeatureSetExtractor
{
private:
    relative_operator _operator;

public:
    CooccurrenceMatrixBasedFeatureSet(relative_operator _operator);
    virtual ~CooccurrenceMatrixBasedFeatureSet() { }

    void addFeature(FeatureExtractor *featureExtractor) override;
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
};

class CooccurrenceMatrixBasedDescriptor : public FeatureExtractor
{
private:
    relative_operator _operator;

protected:
    cv::Mat calculateCooccurenceMatrix(const cv::Mat& image) const;
    cv::Mat calculateProbabilityCooccurenceMatrix(const cv::Mat& image) const;

public:
    /*
    * _operator: callback function to be called
    * when deciding which pixel is relative to current pixel
    * from left to right, top to bottom
    */
    CooccurrenceMatrixBasedDescriptor(relative_operator _operator);
    ~CooccurrenceMatrixBasedDescriptor() { }

    virtual std::vector<val_type> extractFeature(const cv::Mat& image, const cv::Mat& cooccurenceMatrix) const = 0;
};

#endif // COOCCURRENCEMATRIXBASEDDESCRIPTOR_H
