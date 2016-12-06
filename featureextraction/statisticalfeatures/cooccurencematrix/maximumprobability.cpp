#include "maximumprobability.h"

MaximumProbability::MaximumProbability(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

MaximumProbability::~MaximumProbability()
{ }

std::vector<double> MaximumProbability::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    double maxProb = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
//        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            float prob = probabilityMatrix.at<float>(r, c);
            if (maxProb < prob)
                maxProb = prob;
        }
    }

    return {maxProb};
}
