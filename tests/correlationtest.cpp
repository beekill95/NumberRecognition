#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/correlation.h"
#include "common.h"

TEST(CorrelationTest, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Correlation correlation(nextPixel);
    std::vector<double> con = correlation.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(-0.0005, con[0], 0.00005);
}

TEST(CorrelationTest, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Correlation correlation(nextPixel);
    std::vector<double> con = correlation.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(0.965, con[0], 0.0005);
}

TEST(CorrelationTest, TestWithMixTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    cv::imshow("MixTexture", image);

    Correlation correlation(nextPixel);
    std::vector<double> con = correlation.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(0.8798, con[0], 0.00005);
}
