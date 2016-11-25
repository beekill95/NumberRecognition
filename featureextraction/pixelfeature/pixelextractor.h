#ifndef PIXELEXTRACTOR_H
#define PIXELEXTRACTOR_H

#include "../featureextractor.h"

class PixelExtractor : public FeatureExtractor
{
public:
    PixelExtractor();
    ~PixelExtractor();

    std::vector<double> extractFeature(const cv::Mat& image) const override;
};

#endif // PIXELEXTRACTOR_H
