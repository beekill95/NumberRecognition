#include "correlation.h"

Correlation::Correlation(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Correlation::~Correlation()
{ }

double sum(const float* array, int size = 256)
{
    double total = 0.0;
    for (int i = 0; i < size; ++i)
        total += array[i];
    return total;
}

double calculateMeanRow(const cv::Mat& probabilityMatrix)
{
    // TODO
    return 0.0;
}

double calculateMeanColumn(const cv::Mat& probabilityMatrix)
{
    // TODO
    return 0.0;
}

double calculateVarianceRow(const cv::Mat& probabilityMatrix, double meanRow)
{
    // TODO
    return 0.0;
}

double calculateVarianceColumn(const cv::Mat& probabilityMatrix, double meanColumn)
{
    // TODO
    return 0.0;
}

std::vector<double> Correlation::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityOccurenceMatrix(image);

    // calculate mean value in row and column
    double meanRow = calculateMeanRow(probabilityMatrix);
    double meanCol = calculateMeanColumn(probabilityMatrix);

    // calculate variance value in row and column
    double varianceRow = calculateVarianceRow(probabilityMatrix, meanRow);
    double varianceCol = calculateVarianceColumn(probabilityMatrix, meanCol);

    // calculate the correlation
    double correlation = 0.0;
    for (int r = 0; r < 256; ++r) {
        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < 256; ++c) {
            float prob = row[c];

            correlation += (r - meanRow) * (c - meanCol) * prob;
        }
    }

    return {correlation / (varianceCol * varianceRow)};
}
