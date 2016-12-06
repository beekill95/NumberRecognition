#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/contrast.h"
#include "common.h"

TEST(ContrastTest, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Contrast contrast(nextPixel);
    std::vector<double> con = contrast.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(10838, con[0], 0.5);
}

TEST(ContrastTest, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Contrast contrast(nextPixel);
    std::vector<double> con = contrast.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(570, con[0], 0.5);
}

TEST(ContrastTest, TestWithMixedTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Contrast contrast(nextPixel);
    std::vector<double> con = contrast.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(1356, con[0], 0.5);
}
