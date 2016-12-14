#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "../featureextraction/statisticalfeatures/histogram/averageentropy.h"
#include "common.h"

TEST(AverageEntropy, TestWithSoNam) {
    cv::Mat image = cv::imread(SO_NAM_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    AverageEntropy entropy;
    std::vector<val_type> en = entropy.extractFeature(image);

    ASSERT_EQ(1, en.size());
    EXPECT_NEAR(1.8285, en[0], 0.00005);
}

