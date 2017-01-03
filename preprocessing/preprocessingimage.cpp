#include "preprocessingimage.h"

#include <opencv2/imgproc/imgproc.hpp>

std::vector<cv::Mat> PreprocessingImage::preprocess(const std::vector<cv::Mat> &images) const
{
    std::vector<cv::Mat> preprocessedImages;
    preprocessedImages.reserve(images.size());

    const int MEDIAN_KERNEL_LENGTH = 3;
    const int GAUSS_KERNEL_SIZE = 7;

    for (size_t i = 0; i < images.size(); ++i) {
        const cv::Mat& image = images.at(i);

        cv::Mat preprocessedImage = image.clone();

        // apply median filter
//        cv::medianBlur(image, preprocessedImage, MEDIAN_KERNEL_LENGTH);
        cv::GaussianBlur(image, preprocessedImage, cv::Size(GAUSS_KERNEL_SIZE, GAUSS_KERNEL_SIZE), 0, 0);

        // apply binary threhold method
        cv::threshold(preprocessedImage, preprocessedImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

        // push back to result vector
        preprocessedImages.push_back(preprocessedImage);
    }

    return preprocessedImages;
}
