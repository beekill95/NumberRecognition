#include "uniformitycooccurence.h"

UniformityCooccurence::UniformityCooccurence(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

UniformityCooccurence::~UniformityCooccurence()
{ }

std::vector<val_type> UniformityCooccurence::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityCooccurenceMatrix(image);

    val_type uniformity = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            val_type prob = probabilityMatrix.at<float>(r, c);
            uniformity += prob * prob;
        }
    }

    return {uniformity};
}

std::vector<val_type> UniformityCooccurence::extractFeature(const cv::Mat &image, const cv::Mat &cooccurMatrix) const
{
    val_type uniformity = 0.0;
    for (int r = 0; r < cooccurMatrix.rows; ++r) {

        for (int c = 0; c < cooccurMatrix.cols; ++c) {
            val_type prob = cooccurMatrix.at<float>(r, c);
            uniformity += prob * prob;
        }
    }

    return {uniformity};
}
