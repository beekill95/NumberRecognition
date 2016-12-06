#include "cooccurrencematrixbaseddescriptor.h"

#include <opencv2/opencv.hpp>
#include <iostream>

CooccurrenceMatrixBasedDescriptor::CooccurrenceMatrixBasedDescriptor(relative_operator _operator)
    : _operator(_operator)
{ }

cv::Mat CooccurrenceMatrixBasedDescriptor::calculateOccurenceMatrix(const cv::Mat &image) const
{
    cv::Mat cooccurenceMatrix(256, 256, CV_32SC1, cvScalar(0));

    // kiem tra xem ma tran vua tao co bang 0
//    for (int i = 0; i < 256; ++i)
//        for (int j = 0; j < 256; ++j)
//            if (cooccurenceMatrix.at<int>(i, j) != 0)
//                std::cerr << "\nMa tran cooccurent khong bang 0 tai vi tri (" << i << ", " << j << ")";

    for (int r = 0; r < image.rows; ++r) {
//        const unsigned char* pixelRow = image.ptr(r);

        for (int c = 0; c < image.cols; ++c) {
            unsigned char pixel = image.at<unsigned char>(r, c);

            cv::Point relativePixelCoord = _operator(cv::Point(r, c));
            if (relativePixelCoord.x >= 0 && relativePixelCoord.x < image.rows
                    && relativePixelCoord.y >= 0 && relativePixelCoord.y < image.cols) {
                unsigned char relativePixel = image.at<unsigned char>(relativePixelCoord.x, relativePixelCoord.y);

                cooccurenceMatrix.at<int>(pixel, relativePixel) += 1;
            }
        }
    }

    return cooccurenceMatrix;
}

cv::Mat CooccurrenceMatrixBasedDescriptor::calculateProbabilityOccurenceMatrix(const cv::Mat &image) const
{
//    unsigned char data[][6] = {
//        {0, 0, 6, 4, 2, 1},
//        {4, 0, 5, 0, 1, 4},
//        {7, 7, 5, 7, 0, 1},
//        {3, 2, 3, 4, 4, 0},
//        {7, 6, 7, 6, 5, 1},
//        {6, 7, 5, 1, 5, 1},
//    };
//    cv::Mat myImage(6, 6, CV_8U, (void*)data);

//    std::cout << calculateOccurenceMatrix(myImage);

//    cv::imshow("original", image);
//    cv::waitKey(0);

    cv::Mat cooccurrenceMatrix = calculateOccurenceMatrix(image);

    cv::Mat result;


//    std::cout << '\n' << '\n' << cooccurrenceMatrix << std::endl;
//    cv::normalize(cooccurrenceMatrix, result, 0, 255, CV_MINMAX, CV_8UC1);
//    cv::imshow("Image", result);
//    std::cout << result << std::endl;
//    cv::waitKey(0);

    // so luong cap pixel thoa man _operator
    int numberOfPairs = 0;
    for (int r = 0; r < cooccurrenceMatrix.rows; ++r) {
//        const int* row = cooccurrenceMatrix.ptr<int>(r);

        for (int c = 0; c < cooccurrenceMatrix.cols; ++c)
            numberOfPairs += cooccurrenceMatrix.at<int>(r, c);
    }

    // phan phoi xac xuat tren toan ma tran cooccurrence matrix
    cv::Mat probabilityMatrix(cooccurrenceMatrix.rows, cooccurrenceMatrix.cols, CV_32FC1);
    for (int r = 0; r < cooccurrenceMatrix.rows; ++r) {
//        const int* row = cooccurrenceMatrix.ptr<int>(r);
//        float* probRow = probabilityMatrix.ptr<float>(r);

        for (int c = 0; c < cooccurrenceMatrix.cols; ++c)
            //probRow[c] = 1.0f * row[c] / numberOfPairs;
            probabilityMatrix.at<float>(r, c) = cooccurrenceMatrix.at<int>(r, c) * 1.0f / numberOfPairs;
    }

//    result = probabilityMatrix * 255;
//    cv::imshow("Image", result);
//    cv::waitKey(0);

    return probabilityMatrix;
}
