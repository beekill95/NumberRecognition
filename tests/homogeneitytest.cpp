#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/homogeneity.h"
#include "common.h"

TEST(HomogeneityTest, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Homogeneity homo(nextPixel);
    std::vector<double> maxProb = homo.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.0366, maxProb[0], 0.00005);
}

TEST(HomogeneityTest, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Homogeneity homo(nextPixel);
    std::vector<double> maxProb = homo.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.0824, maxProb[0], 0.00005);
}

TEST(HomogeneityTest, TestWithMixTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Homogeneity homo(nextPixel);
    std::vector<double> maxProb = homo.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.2048, maxProb[0], 0.00005);
}
