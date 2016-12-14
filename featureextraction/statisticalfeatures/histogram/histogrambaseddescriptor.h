#ifndef HISTOGRAMBASEDDESCRIPTOR_H
#define HISTOGRAMBASEDDESCRIPTOR_H

#include "../../featureextractor.h"
#include "../../featuresetextractor.h"

class HistogramBaseFeatureSet : public FeatureSetExtractor
{
public:
    virtual ~HistogramBaseFeatureSet() {}

    void addFeature(FeatureExtractor* featureExtractor) override;

    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
};

class HistogramBasedDescriptor : public FeatureExtractor
{
protected:
    void calculateHistogram(const cv::Mat& image, int* histogram) const;
    void calculateHistogram(const cv::Mat& image, val_type* histogram) const;
    val_type meanHistogram(const val_type* histogram) const;

public:
    HistogramBasedDescriptor() {}
    virtual ~HistogramBasedDescriptor() {}

    virtual std::vector<val_type> extractFeature(const val_type* histogram) const = 0;
};

#endif // HISTOGRAMBASEDDESCRIPTOR_H
