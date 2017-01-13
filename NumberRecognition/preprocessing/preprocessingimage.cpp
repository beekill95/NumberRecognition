#include "preprocessingimage.h"

#include <opencv2/imgproc/imgproc.hpp>

cv::Mat toBinaryImage(const cv::Mat& image)
{
    cv::Mat binaryImage = image.clone();

    for (int r = 0; r < binaryImage.rows; ++r) {
        const unsigned char* originalRow = image.ptr(r);
        unsigned char* row = binaryImage.ptr(r);

        for (int c = 0; c < binaryImage.cols; ++c)
            row[c] = (originalRow[c] > 0) ?  255: 0;
    }

    return binaryImage;
}

std::vector<cv::Mat> PreprocessingImage::preprocess(const std::vector<cv::Mat> &images) const
{
    std::vector<cv::Mat> preprocessedImages;
    preprocessedImages.reserve(images.size());

//    const int MEDIAN_KERNEL_LENGTH = 3;
    const int GAUSS_KERNEL_SIZE = 7;

    for (size_t i = 0; i < images.size(); ++i) {
        const cv::Mat& image = images.at(i);

        cv::Mat preprocessedImage = image.clone();

        // apply median filter
//        cv::medianBlur(image, preprocessedImage, MEDIAN_KERNEL_LENGTH);
        cv::GaussianBlur(image, preprocessedImage, cv::Size(GAUSS_KERNEL_SIZE, GAUSS_KERNEL_SIZE), 0, 0);

        // apply binary threhold method
//        cv::threshold(preprocessedImage, preprocessedImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

        preprocessedImage = toBinaryImage(image);

        // push back to result vector
        preprocessedImages.push_back(preprocessedImage);
    }

    return preprocessedImages;
}
