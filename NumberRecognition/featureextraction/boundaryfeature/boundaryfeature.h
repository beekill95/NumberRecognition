#ifndef BOUNDARYFEATURE_H
#define BOUNDARYFEATURE_H

#include "../featureextractor.h"

class BoundaryFeature : public FeatureExtractor
{
private:
    cv::Point cellSize;
    int maxBoundaryLength;

public:
    BoundaryFeature(const cv::Point& cellSize, int maxBoundaryLength);
    ~BoundaryFeature() { }

    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    int getFeatureCount() const override {return maxBoundaryLength;}
};

#endif // BOUNDARYFEATURE_H
