#include "moment.h"

#include <cmath>

Moment::Moment(int count)
{
    if (count < 2)
        count = 2;
    nthMoments = std::vector<int>(count - 1);

    for (int i = 2; i <= count; ++i)
        nthMoments[i - 2] = i;
}

Moment::Moment(const std::vector<int> &moments)
    : nthMoments(moments)
{ }

Moment::~Moment()
{
    nthMoments.clear();
}

val_type extractMomentNth(val_type mean, const val_type* histogramDistribution, int momentNth)
{
    val_type nthMoment = 0.0;
    for (int i = 0; i < 256; ++i) {
        nthMoment += pow(i - mean, momentNth) * histogramDistribution[i];
    }

    return nthMoment;
}

std::vector<val_type> Moment::extractFeature(const cv::Mat &image) const
{
    // calculate histogram
    val_type histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    // calculate mean histogram
    val_type mean = meanHistogram(histogramDistribution);

    // calculate moments
    std::vector<val_type> moments(nthMoments.size());
    for (size_t i = 0; i < nthMoments.size(); ++i)
        moments[i] = extractMomentNth(mean, histogramDistribution, nthMoments[i]);

    return moments;
}

std::vector<val_type> Moment::extractFeature(const val_type *histogram) const
{
    // calculate mean histogram
    val_type mean = meanHistogram(histogram);

    // calculate moments
    std::vector<val_type> moments(nthMoments.size());
    for (size_t i = 0; i < nthMoments.size(); ++i)
        moments[i] = extractMomentNth(mean, histogram, nthMoments[i]);

    return moments;
}
