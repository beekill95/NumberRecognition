#include "correlation.h"

Correlation::Correlation(relative_operator _operator)
    : CooccurrenceMatrixBasedDescriptor(_operator)
{ }

Correlation::~Correlation()
{ }

val_type sum(const float* array, int size = 256)
{
    val_type total = 0.0;
    for (int i = 0; i < size; ++i)
        total += array[i];
    return total;
}

val_type calculateMeanRow(const cv::Mat& probabilityMatrix)
{
    val_type meanRow = 0.0;
    for (int r = 0; r < probabilityMatrix.rows; ++r) {
        val_type totalColumn = 0.0;

        const float* row = probabilityMatrix.ptr<float>(r);
        for (int c = 0; c < probabilityMatrix.cols; ++c)
            totalColumn += row[c];

        meanRow += totalColumn * r;
    }
    return meanRow;
}

val_type calculateMeanColumn(const cv::Mat& probabilityMatrix)
{
    val_type meanColumn = 0.0;
    for (int c = 0; c < probabilityMatrix.cols; ++c) {
        val_type totalRow = 0.0;

        for (int r = 0; r < probabilityMatrix.rows; ++r)
            totalRow += probabilityMatrix.at<float>(r, c);

        meanColumn += c * totalRow;
    }

    return meanColumn;
}

val_type calculateVarianceRow(const cv::Mat& probabilityMatrix, double meanRow)
{
    val_type varianceRow = 0.0;

    for (int r = 0; r < probabilityMatrix.rows; ++r) {
        val_type totalColumn = 0.0;

        const float* row = probabilityMatrix.ptr<float>(r);
        for (int c = 0; c < probabilityMatrix.cols; ++c)
            totalColumn += row[c];

        varianceRow += totalColumn * (meanRow - r) * (meanRow - r);
    }

    return varianceRow;
}

val_type calculateVarianceColumn(const cv::Mat& probabilityMatrix, double meanColumn)
{
    val_type varianceCol = 0.0;

    for (int c = 0; c < probabilityMatrix.cols; ++c) {
        val_type totalRow = 0.0;

        for (int r = 0; r < probabilityMatrix.rows; ++r)
            totalRow += probabilityMatrix.at<float>(r, c);

        varianceCol += totalRow * (meanColumn - c) * (meanColumn - c);
    }

    return varianceCol;
}

std::vector<val_type> Correlation::extractFeature(const cv::Mat &image) const
{
    cv::Mat probabilityMatrix = calculateProbabilityCooccurenceMatrix(image);

    // calculate mean value in row and column
    val_type meanRow = calculateMeanRow(probabilityMatrix);
    val_type meanCol = calculateMeanColumn(probabilityMatrix);

    // calculate variance value in row and column
    val_type varianceRow = calculateVarianceRow(probabilityMatrix, meanRow);
    val_type varianceCol = calculateVarianceColumn(probabilityMatrix, meanCol);

    // calculate the correlation
    val_type correlation = 0.0;
    for (int r = 0; r < 256; ++r) {
        const float* row = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < 256; ++c) {
            float prob = row[c];

            correlation += (r - meanRow) * (c - meanCol) * prob;
        }
    }

    return {correlation / (varianceCol * varianceRow)};
}

std::vector<val_type> Correlation::extractFeature(const cv::Mat &image, const cv::Mat &cooccurMatrix) const
{
    // calculate mean value in row and column
    val_type meanRow = calculateMeanRow(cooccurMatrix);
    val_type meanCol = calculateMeanColumn(cooccurMatrix);

    // calculate variance value in row and column
    val_type varianceRow = calculateVarianceRow(cooccurMatrix, meanRow);
    val_type varianceCol = calculateVarianceColumn(cooccurMatrix, meanCol);

    // calculate the correlation
    val_type correlation = 0.0;
    for (int r = 0; r < 256; ++r) {
        const float* row = cooccurMatrix.ptr<float>(r);

        for (int c = 0; c < 256; ++c) {
            val_type prob = row[c];

            correlation += (r - meanRow) * (c - meanCol) * prob;
        }
    }

    return {correlation / (varianceCol * varianceRow)};
}
