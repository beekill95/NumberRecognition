#include "boundaryfeature.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

#define DIVIDE_CV_POINT(lhs, rhs) (cv::Point(lhs.x / rhs.x, lhs.y / rhs.y))

/*
* largerCellSize: relative to original cell
*/
std::vector<cv::Point> subsample(const std::vector<cv::Point>& smallBoundary, const cv::Point& largeCellSize)
{
    std::vector<cv::Point> largeBoundary;

    largeBoundary.push_back(DIVIDE_CV_POINT(smallBoundary[0], largeCellSize));

    for (size_t i = 1; i < smallBoundary.size(); ++i) {
        cv::Point largePoint = DIVIDE_CV_POINT(smallBoundary[i], largeCellSize);
        const cv::Point& lastPoint = largeBoundary[largeBoundary.size() - 1];

        if (largePoint.x != lastPoint.x || largePoint.y != lastPoint.y) {
            largeBoundary.push_back(largePoint);
        }
    }

    return largeBoundary;
}

std::vector<int> invariantChainCode(const std::vector<int>& chainCode)
{
    // convert vector to string
    auto vector2String = [](const std::vector<int>& vec, int startPoint) {
        std::string str;
        str.reserve(vec.size());

        for (int i = startPoint; i < vec.size(); ++i)
            str += std::to_string(vec[i]);

        for (int i = 0; i < startPoint; ++i)
            str += std::to_string(vec[i]);

        return str;
    };

    // copy vector from this start point
    // if meet end point then roll back
    auto copyFrom = [](const std::vector<int>& vec, int startPoint) {
        std::vector<int> copied;
        copied.reserve(vec.size());

        for (int i = startPoint; i < vec.size(); ++i)
            copied.push_back(vec[i]);

        for (int i = 0; i < startPoint; ++i)
            copied.push_back(vec[i]);

        return copied;
    };

    int minIndex = 0;
    for (int i = 1; i < chainCode.size(); ++i) {
        std::string minStr = vector2String(chainCode, minIndex);
        std::string curStr = vector2String(chainCode, i);

        if (curStr.compare(minStr) < 0)
            minIndex = i;
    }

    return copyFrom(chainCode, minIndex);
}

std::vector<int> generateChainCode(const std::vector<cv::Point>& boundary)
{
    std::vector<int> chainCode;
    chainCode.reserve(boundary.size());

    // convert direction vector to feeman code
    auto getFeemanCode = [](const cv::Point& vec) -> int {
        if (vec.y == 0) {
            return vec.x == 1 ? 0 : 4;
        } else if (vec.y < 0) {
            return 2 - vec.x;
        } else {
            return 6 + vec.x;
        }
    };

    for (size_t i = 0; i < boundary.size() - 1; ++i) {
        const cv::Point& cur = boundary[i];
        const cv::Point& next = boundary[i + 1];
        cv::Point diff = next - cur;

        chainCode.push_back(getFeemanCode(diff));
    }

    {
        const cv::Point& last = boundary[boundary.size() - 1];
        const cv::Point& first = boundary[0];

        chainCode.push_back(getFeemanCode(first - last));
    }

    // make chain code invariant to starting point
    return invariantChainCode(chainCode);
}
\
// make chain code invariant to rotation
std::vector<val_type> generateFirstDifference(const std::vector<int>& chainCode)
{
    std::vector<val_type> firstDifference;
    firstDifference.reserve(chainCode.size());

    // calculate first difference
    auto getFirstDifference = [](int cur, int next) {
        int diff = -(cur - next);
        return diff >= 0 ? diff : diff + 8;
    };

    for (size_t i = 0; i < chainCode.size() - 1; ++i) {
        int cur = chainCode[i];
        int next = chainCode[i + 1];

        firstDifference.push_back(getFirstDifference(cur, next));
    }

    // between the last and first
    {
        int last = chainCode[chainCode.size() - 1];
        int first = chainCode[0];

        firstDifference.push_back(getFirstDifference(last, first));
    }

    return firstDifference;
}

// find the longest boundary in the boundaries
std::vector<cv::Point> getLongestBoundary(const std::vector<std::vector<cv::Point> >& boundaries)
{
    int max = boundaries[0].size();
    int index = 0;
    for (int i = 1; i < boundaries.size(); ++i)
        if (max < boundaries[i].size()) {
            max = boundaries[i].size();
            index = i;
        }

    return boundaries[index];
}

BoundaryFeature::BoundaryFeature(const cv::Point &cellSize, int maxBoundaryLength)
    : cellSize(cellSize), maxBoundaryLength(maxBoundaryLength)
{ }

std::vector<val_type> BoundaryFeature::extractFeature(const cv::Mat &image) const
{
    std::vector<std::vector<cv::Point> > boundaries;

//    cv::imshow("Binary image", image);
    cv::findContours(image, boundaries, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // draw the boundary
//    cv::Mat drawing = cv::Mat::zeros(image.size(), CV_8UC3);
//    for (size_t i = 0; i < boundaries.size(); ++i) {
//        cv::Scalar color = cv::Scalar(255, 255, 0);
//        cv::drawContours( drawing, boundaries, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
//    }

//    cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//    cv::imshow( "Contours", drawing );


    // check for boundaries found
    // if it's greater than 1
    // warning
    if (boundaries.size() != 1) {
        std::cerr << "\nMore than 1 boundary found in image" << std::endl;

        // draw the boundary
//            cv::Mat drawing = cv::Mat::zeros(image.size(), CV_8UC3);
//            for (size_t i = 0; i < boundaries.size(); ++i) {
//                cv::Scalar color = cv::Scalar(255, 255, 0);
//                cv::drawContours( drawing, boundaries, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
//            }

//            cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//            cv::imshow( "Contours", drawing );

        // show the image


//            cv::waitKey();
    }

    // subsampling
    std::vector<cv::Point> largeBoundary = subsample(getLongestBoundary(boundaries), cellSize);

//    if (boundaries.size() != 1) {
////        std::cerr << "\nMore than 1 boundary found in image" << std::endl;

//        // draw the boundary
//        std::vector<std::vector<cv::Point> > largeBoundaries;
//            largeBoundaries.push_back(getLongestBoundary(boundaries));
//            cv::Mat largeDrawing = cv::Mat::zeros(image.size(), CV_8UC3);
//            {
//                cv::Scalar color = cv::Scalar(0, 255, 255);
//                cv::drawContours( largeDrawing, largeBoundaries, 0, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
//            }

//            cv::namedWindow( "Subsample", CV_WINDOW_AUTOSIZE );
//            cv::imshow( "Subsample", largeDrawing );

//            cv::waitKey();
//    }
//    std::vector<std::vector<cv::Point> > largeBoundaries;
//    largeBoundaries.push_back(largeBoundary);
//    cv::Mat largeDrawing = cv::Mat::zeros(image.size(), CV_8UC3);
//    {
//        cv::Scalar color = cv::Scalar(0, 255, 255);
//        cv::drawContours( largeDrawing, largeBoundaries, 0, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
//    }

//    cv::namedWindow( "Subsample", CV_WINDOW_AUTOSIZE );
//    cv::imshow( "Subsample", largeDrawing );

//    cv::waitKey();

    // generate chain code
    std::vector<int> chainCode = generateChainCode(largeBoundary);

    // generate first difference
    std::vector<val_type> firstDifference = generateFirstDifference(chainCode);

    // return the boundary first difference descriptor
    std::vector<val_type> descriptorVector(maxBoundaryLength, 0);
//    descriptorVector.(descriptorVector.begin(), firstDifference.begin(), firstDifference.end());
    std::copy(firstDifference.begin(), firstDifference.end(), descriptorVector.begin());

    return descriptorVector;
}
