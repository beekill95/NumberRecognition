#include "homogeneity.h"

Homogeneity::Homogeneity(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Homogeneity::~Homogeneity()
{ }

std::vector<double> Homogeneity::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    double homogeneity = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            homogeneity += row[c] / (1 + abs(r - c));
        }
    }

    return {homogeneity};
}
