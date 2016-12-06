#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/entropy.h"
#include "common.h"

TEST(CooccurrenceEntropyTest, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Entropy entropy(nextPixel);
    std::vector<double> con = entropy.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(15.75, con[0], 0.005);
}

TEST(CooccurrenceEntropyTest, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Entropy entropy(nextPixel);
    std::vector<double> con = entropy.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(6.43, con[0], 0.005);
}

TEST(CooccurrenceEntropyTest, TestWithMixTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Entropy entropy(nextPixel);
    std::vector<double> con = entropy.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(13.58, con[0], 0.005);
}
