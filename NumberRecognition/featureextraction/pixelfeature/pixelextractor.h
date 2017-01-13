#ifndef PIXELEXTRACTOR_H
#define PIXELEXTRACTOR_H

#include "../featureextractor.h"

class PixelExtractor : public FeatureExtractor
{
private:
    int pixelExtracted;

public:
    PixelExtractor(int pixelExtract);
    ~PixelExtractor();

    std::vector<val_type> extractFeature(const cv::Mat& image) const override;
    int getFeatureCount() const override {return pixelExtracted;}
};
#endif // PIXELEXTRACTOR_H
