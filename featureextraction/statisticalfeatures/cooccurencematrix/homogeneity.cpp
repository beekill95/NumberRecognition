#include "homogeneity.h"

Homogeneity::Homogeneity(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Homogeneity::~Homogeneity()
{ }

std::vector<val_type> Homogeneity::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityCooccurenceMatrix(image);

    val_type homogeneity = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            homogeneity += row[c] / (1 + abs(r - c));
        }
    }

    return {homogeneity};
}

std::vector<val_type> Homogeneity::extractFeature(const cv::Mat &image, const cv::Mat &cooccurMatrix) const
{
    val_type homogeneity = 0.0;
    for (int r = 0; r < cooccurMatrix.rows; ++r) {
        const float* row = cooccurMatrix.ptr<float>(r);

        for (int c = 0; c < cooccurMatrix.cols; ++c) {
            homogeneity += row[c] / (1 + abs(r - c));
        }
    }

    return {homogeneity};
}
