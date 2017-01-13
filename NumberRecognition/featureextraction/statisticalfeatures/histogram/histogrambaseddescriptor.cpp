#include "histogrambaseddescriptor.h"
#include <cstring>

void calculateHistogram(const cv::Mat &image, int* histogram)
{
    memset(histogram, 0, 256 * sizeof(int));

    for (int r = 0; r < image.rows; ++r) {
        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c)
            ++histogram[pixelRow[c]];
    }
}

void calculateHistogram(const cv::Mat &image, val_type* histogram)
{
    memset(histogram, 0, 256 * sizeof(val_type));

    for (int r = 0; r < image.rows; ++r) {
        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c)
            ++histogram[pixelRow[c]];
    }

    int totalPixel = image.rows * image.cols;
    for (int i = 0; i < 256; ++i)
        histogram[i] /= totalPixel;
}

val_type histogramMean(const val_type* histogramDistribution)
{
    val_type mean = 0.0;
    for (int i = 0; i < 256; ++i)
        mean += i * histogramDistribution[i];

    return mean;
}

void HistogramBasedDescriptor::calculateHistogram(const cv::Mat &image, int *histogram) const
{
    ::calculateHistogram(image, histogram);
}

void HistogramBasedDescriptor::calculateHistogram(const cv::Mat &image, val_type *histogram) const
{
    ::calculateHistogram(image, histogram);
}

val_type HistogramBasedDescriptor::meanHistogram(const val_type *histogram) const
{
    return histogramMean(histogram);
}

void HistogramBaseFeatureSet::addFeature(FeatureExtractor *featureExtractor)
{
    // check whether current feature belongs to HistogramBasedDescriptor
    HistogramBasedDescriptor* feature = dynamic_cast<HistogramBasedDescriptor*>(featureExtractor);

    // if so
    if (feature != 0)
        FeatureSetExtractor::addFeature(featureExtractor);
}

std::vector<val_type> HistogramBaseFeatureSet::extractFeature(const cv::Mat &image) const
{
    val_type histogram[256];
    calculateHistogram(image, histogram);

    // TODO
    std::vector<val_type> features;
    features.reserve(getFeatureCount());
    for (auto it = featureExtractors.cbegin(); it != featureExtractors.cend(); ++it) {
        HistogramBasedDescriptor* descriptor = (HistogramBasedDescriptor*) (*it);

        std::vector<val_type> f = descriptor->extractFeature(histogram);
        features.insert(features.end(), f.begin(), f.end());
    }

    return features;
}
