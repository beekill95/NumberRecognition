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

double extractMomentNth(double mean, float histogramDistribution[], int momentNth)
{
    double nthMoment = 0.0;
    for (int i = 0; i < 256; ++i) {
        nthMoment += pow(i - mean, momentNth) * histogramDistribution[i];
    }

    return nthMoment;
}

std::vector<double> Moment::extractFeature(const cv::Mat &image) const
{
    // calculate histogram
    float histogramDistribution[256];
    calculateHistogram(image, histogramDistribution);

    // calculate mean histogram
    double mean = histogramMean(histogramDistribution);

    // calculate moments
    std::vector<double> moments(nthMoments.size());
    for (size_t i = 0; i < nthMoments.size(); ++i)
        moments[i] = extractMomentNth(mean, histogramDistribution, nthMoments[i]);

    return moments;
}
