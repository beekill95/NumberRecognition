#include "entropy.h"

Entropy::Entropy(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Entropy::~Entropy()
{ }

std::vector<double> Entropy::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    double entropy = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            if (row[c] != 0.0f)
                entropy += row[c] * log2(row[c]);
        }
    }

    return {-entropy};
}
