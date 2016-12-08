#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "../featureextraction/statisticalfeatures/histogram/relativesmoothness.h"
#include "common.h"

TEST(SmoothnessTest, TestWithSoNam) {
    cv::Mat image = cv::imread(SO_NAM_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    RelativeSmoothness relativeSmoothness;

    std::vector<double> smoothness = relativeSmoothness.extractFeature(image);

    ASSERT_EQ(smoothness.size(), 1);
    EXPECT_NEAR(36.1084, smoothness[0], 0.00005);
}
