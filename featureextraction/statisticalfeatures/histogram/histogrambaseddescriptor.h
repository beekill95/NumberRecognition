#ifndef HISTOGRAMBASEDDESCRIPTOR_H
#define HISTOGRAMBASEDDESCRIPTOR_H

#include "../../featureextractor.h"

class HistogramBasedDescriptor : public FeatureExtractor
{
public:
    HistogramBasedDescriptor() {}
    virtual ~HistogramBasedDescriptor() {}

protected:
    static void calculateHistogram(const cv::Mat& image, int histogram[]);
    static void calculateHistogram(const cv::Mat &image, float histogram[]);
    static double histogramMean(float histogramDistribution[]);
};

#endif // HISTOGRAMBASEDDESCRIPTOR_H
