#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "common.h"
#include "../featureextraction/pixelfeature/pixelextractor.h"

TEST(PixelExtractorTest, TestWithCoarseImage) {
    cv::Mat image = cv::imread(COARSE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    PixelExtractor pixelExtractor(784);
    std::vector<val_type> pixels = pixelExtractor.extractFeature(image);

    ASSERT_EQ(image.rows * image.cols, pixels.size());
    for (int r = 0; r < image.rows; ++r)
        for (int c = 0; c < image.cols; ++c) {
            unsigned char originalPixel = image.at<unsigned char>(r, c);
            unsigned char extractedPixel = (unsigned char) pixels[r * image.cols + c];

            EXPECT_EQ(originalPixel, extractedPixel);
        }
}

TEST(PixelExtractorTest, TestWithSmoothImage) {
    cv::Mat image = cv::imread(SMOOTH_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    PixelExtractor pixelExtractor(784);
    std::vector<val_type> pixels = pixelExtractor.extractFeature(image);

    ASSERT_EQ(image.rows * image.cols, pixels.size());
    for (int r = 0; r < image.rows; ++r)
        for (int c = 0; c < image.cols; ++c) {
            unsigned char originalPixel = image.at<unsigned char>(r, c);
            unsigned char extractedPixel = (unsigned char) pixels[r * image.cols + c];

            EXPECT_EQ(originalPixel, extractedPixel);
        }
}
