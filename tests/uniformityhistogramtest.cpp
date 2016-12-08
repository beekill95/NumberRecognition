#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "../featureextraction/statisticalfeatures/histogram/uniformity.h"
#include "common.h"

TEST(UniformityHistogramTest, TestWithSoNam) {
    cv::Mat image = cv::imread(SO_NAM_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    UniformityHistogram uniformity;
    std::vector<double> uni = uniformity.extractFeature(image);

    ASSERT_EQ(1, uni.size());
    EXPECT_NEAR(0.6264, uni[0], 0.00005);
}
