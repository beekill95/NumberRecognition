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

std::vector<val_type> FeatureSetExtractor::extractFeature(const cv::Mat &image) const
{
    std::vector<val_type> features;
    features.reserve(getFeatureCount());

    for (auto it = featureExtractors.cbegin(); it != featureExtractors.cend(); ++it) {
        std::vector<val_type> f = (*it)->extractFeature(image);

        // append to features
        features.insert(features.end(), f.begin(), f.end());
    }

    return features;
}

//std::vector<std::vector<val_type> > FeatureSetExtractor::batchExtractFeatures(const std::vector<cv::Mat> &images) const
//{
//    std::vector<std::vector<val_type> > batchFeatures(images.size());
//;
//    for (auto imageIter = images.cbegin(); imageIter != images.cend(); ++imageIter) {
//        batchFeatures.push_back(extractFeatures(*imageIter));
//    }

//    return batchFeatures;
//}

int FeatureSetExtractor::getFeatureCount() const
{
    int featureCount = 0;
    for (size_t i = 0; i < featureExtractors.size(); ++i)
        featureCount += featureExtractors[i]->getFeatureCount();

    return featureCount;
}
