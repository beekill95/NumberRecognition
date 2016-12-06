#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/histogram/meanhistogram.h"
#include "common.h"

TEST(TestMeanHistogram, TestWithSmoothImage) {
    cv::Mat image = cv::imread(SMOOTH_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<double> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_EQ(82.64, mean[0]);
}

TEST(TestMeanHistogram, TestWithCoarseImage) {
    cv::Mat image = cv::imread(COARSE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<double> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_EQ(143.56, mean[0]);
}

TEST(TestMeanHistogram, TestWithRegularImage) {
    cv::Mat image = cv::imread(REGULAR_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    MeanHistogram meanHistogram;

    std::vector<double> mean = meanHistogram.extractFeature(image);

    ASSERT_EQ(mean.size(), 1);
    EXPECT_EQ(99.72, mean[0]);
}
