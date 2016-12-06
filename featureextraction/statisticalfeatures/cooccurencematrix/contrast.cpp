#include "contrast.h"

Contrast::Contrast(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Contrast::~Contrast()
{ }

std::vector<double> Contrast::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    double contrast = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
//        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < probabilityMatrix.cols; ++c) {
            contrast += (r - c) * (r - c) * probabilityMatrix.at<float>(r, c);
        }
    }

    return {contrast};
}
