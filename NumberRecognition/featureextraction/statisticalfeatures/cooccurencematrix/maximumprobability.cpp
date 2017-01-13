#include "maximumprobability.h"

MaximumProbability::MaximumProbability(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

MaximumProbability::~MaximumProbability()
{ }

std::vector<val_type> MaximumProbability::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityCooccurenceMatrix(image);

    val_type maxProb = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
//        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            val_type prob = probabilityMatrix.at<float>(r, c);
            if (maxProb < prob)
                maxProb = prob;
        }
    }

    return {maxProb};
}

std::vector<val_type> MaximumProbability::extractFeature(const cv::Mat &image, const cv::Mat &cooccurMatrix) const
{
    val_type maxProb = 0.0;
    for (int r = 0; r < cooccurMatrix.rows; ++r) {
//        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < cooccurMatrix.cols; ++c) {
            val_type prob = cooccurMatrix.at<float>(r, c);
            if (maxProb < prob)
                maxProb = prob;
        }
    }

    return {maxProb};
}
