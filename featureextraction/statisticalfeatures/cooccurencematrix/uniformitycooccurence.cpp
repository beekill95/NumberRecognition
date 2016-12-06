#include "uniformitycooccurence.h"

UniformityCooccurence::UniformityCooccurence(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

UniformityCooccurence::~UniformityCooccurence()
{ }

std::vector<double> UniformityCooccurence::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    double uniformity = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            float prob = probabilityMatrix.at<float>(r, c);
            uniformity += prob * prob;
        }
    }

    return {uniformity};
}
