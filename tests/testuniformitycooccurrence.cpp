#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../featureextraction/statisticalfeatures/cooccurencematrix/uniformitycooccurence.h"
#include "common.h"

TEST(UniformityCooccurenceTest, TestWithRandomImage) {
    cv::Mat image = cv::imread(RANDOM_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    UniformityCooccurence uniform(nextPixel);
    std::vector<val_type> con = uniform.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(0.00002, con[0], 0.000005);
}

TEST(UniformityCooccurenceTest, TestWithPeriodicImage) {
    cv::Mat image = cv::imread(PERIODIC_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    UniformityCooccurence uniform(nextPixel);
    std::vector<val_type> con = uniform.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(0.0123, con[0], 0.00005);
}

TEST(UniformityCooccurenceTest, TestWithMixTextureImage) {
    cv::Mat image = cv::imread(MIX_TEXTURE_IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    UniformityCooccurence uniform(nextPixel);
    std::vector<val_type> con = uniform.extractFeature(image);

    ASSERT_EQ(1, con.size());
    EXPECT_NEAR(0.0036, con[0], 0.00005);
}
