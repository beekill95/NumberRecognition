#include "featuresetextractor.h"

FeatureSetExtractor::FeatureSetExtractor()
{ }

FeatureSetExtractor::FeatureSetExtractor(std::vector<FeatureExtractor *>&& featureExtractors)
    : featureExtractors(featureExtractors)
{ }

FeatureSetExtractor::~FeatureSetExtractor()
{
    for (auto it = featureExtractors.begin(); it != featureExtractors.end(); ++it)
        delete *it;
    featureExtractors.clear();
}

void FeatureSetExtractor::addFeature(FeatureExtractor *featureExtractor)
{
    featureExtractors.push_back(featureExtractor);
}

std::vector<double> FeatureSetExtractor::extractFeatures(const cv::Mat &image) const
{
    std::vector<double> features;

    for (auto it = featureExtractors.cbegin(); it != featureExtractors.cend(); ++it) {
        std::vector<double> f = (*it)->extractFeature(image);

        // append to features
        features.insert(features.end(), f.begin(), f.end());
    }

    return features;
}

std::vector<std::vector<double> > FeatureSetExtractor::batchExtractFeatures(const std::vector<cv::Mat> &images) const
{
    std::vector<std::vector<double> > batchFeatures(images.size());
;
    for (auto imageIter = images.cbegin(); imageIter != images.cend(); ++imageIter) {
        batchFeatures.push_back(extractFeatures(*imageIter));
    }

    return batchFeatures;
}
