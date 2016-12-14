#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/histogram/meanhistogram.h"
#include "common.h"

TEST(TestMeanHistogram, TestWithSmoothImage) {
    cv::Mat image = cv::imread(SMOOTH_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<val_type> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_NEAR(80.1331, mean[0], 0.00005);
}

TEST(TestMeanHistogram, TestWithCoarseImage) {
    cv::Mat image = cv::imread(COARSE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<val_type> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_NEAR(86.7380, mean[0], 0.0005);
}

TEST(TestMeanHistogram, TestWithRegularImage) {
    cv::Mat image = cv::imread(REGULAR_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<val_type> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_NEAR(113.9048, mean[0], 0.00005);
}

TEST(TestMeanHistogram, TestWithSoNam) {
    cv::Mat image = cv::imread(SO_NAM_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<val_type> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_NEAR(36.1084, mean[0], 0.00005);
}
