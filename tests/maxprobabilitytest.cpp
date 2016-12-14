#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/maximumprobability.h"
#include "common.h"

TEST(TestMaxProbability, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    MaximumProbability maximumProbability(nextPixel);
    std::vector<val_type> maxProb = maximumProbability.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.00006, maxProb[0], 0.000005);
}

TEST(TestMaxProbability, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    MaximumProbability maximumProbability(nextPixel);
    std::vector<val_type> maxProb = maximumProbability.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.015, maxProb[0], 0.0005);
}

TEST(TestMaxProbability, TestWithMixedTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    MaximumProbability maximumProbability(nextPixel);
    std::vector<val_type> maxProb = maximumProbability.extractFeature(image);

    ASSERT_EQ(1, maxProb.size());
    EXPECT_NEAR(0.0589, maxProb[0], 0.00005);
}
