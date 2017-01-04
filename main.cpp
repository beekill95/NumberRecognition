#include "mnistloader/mnistloader.h"

#include "preprocessing/preprocessingimage.h"

#include "recognizer/recognizer.h"
#include "recognizer/knearestneighbors.h"
#include "recognizer/neuralnetwork.h"

#include "featureextraction/pixelfeature/pixelfeature.h"
#include "featureextraction/statisticalfeatures/statisticalfeature.h"
#include "featureextraction/featuresetextractor.h"
#include "featureextraction/boundaryfeature/boundaryfeature.h"

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
#define IMAGE_TESTING_DATA "data/t10k-images.idx3-ubyte"
#define LABEL_TRAINING_DATA "data/train-labels.idx1-ubyte"
#define LABEL_TETSTING_DATA "data/t10k-labels.idx1-ubyte"

#define IMAGE_COUNT 60000
#define TEST_IMAGE_COUNT 10000
#define SMALL_IMAGE_COUNT 2000

using namespace std;
using namespace cv;

cv::Point relativeTo(const cv::Point& first) {
    return cv::Point(first.x, first.y + 1);
}

bool isEnough(bool isBinFull[])
{
    bool isEnough = isBinFull[0];
    for (int i = 1; i < 10; ++i)
        isEnough = isEnough && isBinFull[i];
    return isEnough;
}

void printVector(const std::vector<val_type>& vec)
{
    std::cout << '\n';
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
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

    std::vector<float> dataLabels(IMAGE_COUNT);
    read_Mnist_Label(LABEL_TRAINING_DATA, dataLabels);

    // check whether the data file is loaded successfully
    if (dataImages.size() == 0 || dataLabels.size() == 0) {
        std::cerr << "Cannot load data! Aborting!" << std::endl;
        return 0;
    }

    // only using a small number of images of each number
    // for faster training
    std::vector<cv::Mat> smallDataImages;
    smallDataImages.reserve(SMALL_IMAGE_COUNT * 10);
    std::vector<float> smallDataLabels;
    smallDataLabels.reserve(SMALL_IMAGE_COUNT * 10);
    int numberBinCount[10] = {0};
    bool isBinFull[10] = {false};
    int _i = 0;
    while (!isEnough(isBinFull)) {
        int label = (int) dataLabels[_i];

        if (!isBinFull[label]) {
            // tang bien dem
            ++numberBinCount[label];

            // bo vao du lieu
            smallDataImages.push_back(dataImages[_i]);
            smallDataLabels.push_back(dataLabels[_i]);

            // kiem tra xem da day
            if (numberBinCount[label] == SMALL_IMAGE_COUNT)
                isBinFull[label] = true;
        }

        ++_i;
    }

    // preprocess image
    PreprocessingImage preprocessingImage;

    std::vector<cv::Mat> preprocessImages = preprocessingImage.preprocess(dataImages);
//    std::vector<cv::Mat> preprocessImages = preprocessingImage.preprocess(smallDataImages);
//    cv::imshow("so nam", preprocessImages[0]);
//    cv::waitKey(0);

    // pixel extractor
    // PixelExtractor pixelExtractor;

    // boundary extractor
//    BoundaryFeature boundaryFeature(cv::Point(4, 4), 40);

//    printVector(boundaryFeature.extractFeature(preprocessImages[0]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[11]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[35]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[47]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[65]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[100]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[132]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[138]));
//    printVector(boundaryFeature.extractFeature(preprocessImages[145]));
//    int x;
//    std::cin >> x;


    // feature set extractor
    FeatureSetExtractor featureSetExtractor;
//    featureSetExtractor.addFeature(new PixelExtractor(784));
    featureSetExtractor.addFeature(new BoundaryFeature(cv::Point(4, 4), 40));

    // add all statistical features
//    HistogramBaseFeatureSet* histogramFeatureSet = new HistogramBaseFeatureSet();
//    histogramFeatureSet->addFeature(new AverageEntropy());
//    histogramFeatureSet->addFeature(new MeanHistogram());
//    histogramFeatureSet->addFeature(new Moment(5));
//    histogramFeatureSet->addFeature(new RelativeSmoothness());
//    histogramFeatureSet->addFeature(new UniformityHistogram());

//    featureSetExtractor.addFeature(histogramFeatureSet);

//    CooccurrenceMatrixBasedFeatureSet* cooccurMatFeatureSet = new CooccurrenceMatrixBasedFeatureSet(relativeTo);
//    cooccurMatFeatureSet->addFeature(new Contrast(relativeTo));
//    cooccurMatFeatureSet->addFeature(new Correlation(relativeTo));
//    cooccurMatFeatureSet->addFeature(new Entropy(relativeTo));
//    cooccurMatFeatureSet->addFeature(new Homogeneity(relativeTo));
//    cooccurMatFeatureSet->addFeature(new MaximumProbability(relativeTo));
//    cooccurMatFeatureSet->addFeature(new UniformityCooccurence(relativeTo));

//    featureSetExtractor.addFeature(cooccurMatFeatureSet);

    // trich xuat ra dac trung
    std::vector<std::vector<val_type> > inputs, outputs;
    inputs.reserve(IMAGE_COUNT);
    outputs.reserve(IMAGE_COUNT);
    for (int i = 0; i < IMAGE_COUNT; ++i) {
        inputs.push_back(featureSetExtractor.extractFeature(preprocessImages[i]));
        outputs.push_back({dataLabels[i]});
    }

    // clear images to save some space
    dataImages.clear();
    dataLabels.clear();
    preprocessImages.clear();

    // k - nearest neighbors
    int neighbourCount = 21;
    KNearestNeighbors kNearestNeighbors(neighbourCount);

    // neural network
    std::vector<int> hiddenLayers = {100};
    NeuralNetwork neuralNetwork(featureSetExtractor.getFeatureCount(), hiddenLayers);
    neuralNetwork.setMaxEpochs(300);
    neuralNetwork.setLearningMomentum(0.9);
    neuralNetwork.setLearningRate(0.001);
    neuralNetwork.setDesiredError(0.17);
    neuralNetwork.setTrainingType(BatchTraining);

    NeuralNetwork* nn = NeuralNetwork::deserialize();

    Recognizer* recognizer = &neuralNetwork;

    // training and validating
    Validator validator;
    validator.validate(recognizer, inputs, outputs);

    // save neural network to file
//    neuralNetwork.serialize();

    // user interaction
    // load data
    std::vector<cv::Mat> testingImages;
    const int TESTING_IMAGE_COUNT = 10000;
    testingImages.reserve(TESTING_IMAGE_COUNT);
    read_Mnist(IMAGE_TESTING_DATA, testingImages);

    std::vector<float> testingLabels(TESTING_IMAGE_COUNT);
    read_Mnist_Label(LABEL_TETSTING_DATA, testingLabels);

    std::vector<cv::Mat> preprocessedTestingImages = preprocessingImage.preprocess(testingImages);
    std::vector<std::vector<val_type> > inputTesting, outputTesting;
    inputTesting.reserve(TESTING_IMAGE_COUNT);
    outputTesting.reserve(TESTING_IMAGE_COUNT);
    for (int i = 0; i < TESTING_IMAGE_COUNT; ++i) {
        inputTesting.push_back(featureSetExtractor.extractFeature(preprocessedTestingImages[i]));
        outputTesting.push_back({testingLabels[i]});
    }

    validator.run(recognizer, testingImages, inputTesting, outputTesting);

    // delete
    nn->serialize();
    delete nn;
#endif

    return 0;
}

