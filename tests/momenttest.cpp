#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "../featureextraction/statisticalfeatures/histogram/moment.h"
#include "common.h"

TEST(MomentTest, TestWithSoNam) {
    cv::Mat image = cv::imread(SO_NAM_PATH, CV_LOAD_IMAGE_GRAYSCALE);

    Moment moment({3, 4, 5});
    std::vector<double> moments = moment.extractFeature(image);

    ASSERT_EQ(3, moments.size());
    EXPECT_NEAR(1.0398e+06, moments[0], 0.5);
    EXPECT_NEAR(2.2272e+08, moments[1], 0.5);
    EXPECT_NEAR(4.6349e+10, moments[2], 0.5);
}
