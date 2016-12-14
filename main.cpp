#include "mnistloader/mnistloader.h"

#include "recognizer/recognizer.h"
#include "recognizer/knearestneighbors.h"
#include "recognizer/neuralnetwork.h"

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

    std::vector<float> dataLabels(IMAGE_COUNT);
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
//    featureSetExtractor.addFeature(new PixelExtractor(784));

    // add all statistical features
    HistogramBaseFeatureSet* histogramFeatureSet = new HistogramBaseFeatureSet();
    histogramFeatureSet->addFeature(new AverageEntropy());
    histogramFeatureSet->addFeature(new MeanHistogram());
    histogramFeatureSet->addFeature(new Moment(5));
    histogramFeatureSet->addFeature(new RelativeSmoothness());
    histogramFeatureSet->addFeature(new UniformityHistogram());

    CooccurrenceMatrixBasedFeatureSet* cooccurMatFeatureSet = new CooccurrenceMatrixBasedFeatureSet(relativeTo);
    cooccurMatFeatureSet->addFeature(new Contrast(relativeTo));
    cooccurMatFeatureSet->addFeature(new Correlation(relativeTo));
    cooccurMatFeatureSet->addFeature(new Entropy(relativeTo));
    cooccurMatFeatureSet->addFeature(new Homogeneity(relativeTo));
    cooccurMatFeatureSet->addFeature(new MaximumProbability(relativeTo));
    cooccurMatFeatureSet->addFeature(new UniformityCooccurence(relativeTo));

    featureSetExtractor.addFeature(histogramFeatureSet);
    featureSetExtractor.addFeature(cooccurMatFeatureSet);

    // trich xuat ra dac trung
    std::vector<std::vector<val_type> > inputs, outputs;
    inputs.reserve(IMAGE_COUNT);
    outputs.reserve(IMAGE_COUNT);
    for (int i = 0; i < IMAGE_COUNT; ++i) {
        inputs.push_back(featureSetExtractor.extractFeature(dataImages[i]));
        outputs.push_back({dataLabels[i]});
    }

    // clear images to save some space
    dataImages.clear();
    dataLabels.clear();

    // k - nearest neighbors
    int neighbourCount = 21;
    KNearestNeighbors kNearestNeighbors(neighbourCount);

    // neural network
    std::vector<int> hiddenLayers = {50, 50};
    NeuralNetwork neuralNetwork(featureSetExtractor.getFeatureCount(), hiddenLayers);
    neuralNetwork.setMaxEpochs(50);
    neuralNetwork.setLearningMomentum(0.0);
    neuralNetwork.setLearningRate(0.0001);
    neuralNetwork.setDesiredError(0.15);
    neuralNetwork.setBatchSize(480);
    neuralNetwork.setTrainingType(BatchTraining);

    // training and validating
    Validator validator;
    validator.validate(&neuralNetwork, inputs, outputs);
#endif

    return 0;
}

