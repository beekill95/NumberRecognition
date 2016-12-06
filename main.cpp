#include "mnistloader/mnistloader.h"

#include "recognizer/recognizer.h"
#include "recognizer/knearestneighbors.h"

#include "featureextraction/pixelfeature/pixelfeature.h"
#include "featureextraction/statisticalfeatures/statisticalfeature.h"
#include "featureextraction/featuresetextractor.h"

#include "validator/validator.h"

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include <opencv2/opencv.hpp>

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#define IMAGE_TRAINING_DATA "data/train-images.idx3-ubyte"
#define LABEL_TRAINING_DATA "data/train-labels.idx1-ubyte"

#define IMAGE_COUNT 60000

using namespace std;
using namespace cv;

cv::Point relativeTo(const cv::Point& first) {
    return cv::Point(first.x, first.y + 1);
}

int main(int argc, char** argv)
{
#ifdef GTEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    // load data
    std::vector<cv::Mat> dataImages;
    dataImages.reserve(IMAGE_COUNT);
    read_Mnist(IMAGE_TRAINING_DATA, dataImages);

    std::vector<double> dataLabels(IMAGE_COUNT);
    read_Mnist_Label(LABEL_TRAINING_DATA, dataLabels);

    // check whether the data file is loaded successfully
    if (dataImages.size() == 0 || dataLabels.size() == 0) {
        std::cerr << "Cannot load data! Aborting!" << std::endl;
        return 0;
    }

    // pixel extractor
    // PixelExtractor pixelExtractor;

    // feature set extractor
    FeatureSetExtractor featureSetExtractor;

    // add all statistical features
    featureSetExtractor.addFeature(new AverageEntropy());
    featureSetExtractor.addFeature(new MeanHistogram());
    featureSetExtractor.addFeature(new Moment(5));
    featureSetExtractor.addFeature(new RelativeSmoothness());
    featureSetExtractor.addFeature(new UniformityHistogram());

    featureSetExtractor.addFeature(new Contrast(relativeTo));
    featureSetExtractor.addFeature(new Correlation(relativeTo));
    featureSetExtractor.addFeature(new Entropy(relativeTo));
    featureSetExtractor.addFeature(new Homogeneity(relativeTo));
    featureSetExtractor.addFeature(new MaximumProbability(relativeTo));
    featureSetExtractor.addFeature(new UniformityCooccurence(relativeTo));

    // trich xuat ra dac trung
    std::vector<std::vector<double> > inputs, outputs;
    inputs.reserve(IMAGE_COUNT);
    outputs.reserve(IMAGE_COUNT);
    for (int i = 0; i < IMAGE_COUNT; ++i) {
        inputs.push_back(featureSetExtractor.extractFeatures(dataImages[i]));
        outputs.push_back({dataLabels[i]});
    }

    // k - nearest neighbors
    int neighbourCount = 21;
    Recognizer* kNearestNeighbors = new KNearestNeighbors(neighbourCount);

    // training and validating
    Validator validator;
    validator.validate(kNearestNeighbors, inputs, outputs);

    delete kNearestNeighbors;
#endif

    return 0;
}

