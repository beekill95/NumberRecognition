#ifndef PREPROCESSINGIMAGE_H
#define PREPROCESSINGIMAGE_H

#include <vector>
#include <opencv2/core/core.hpp>

class PreprocessingImage
{
public:
    std::vector<cv::Mat> preprocess(const std::vector<cv::Mat>& images) const;
};

#endif // PREPROCESSINGIMAGE_H
