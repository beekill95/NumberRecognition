#include <common.h>

#define IMAGE_TRAINING_DATA "../data/train-images.idx3-ubyte"
#define IMAGE_TESTING_DATA "../data/t10k-images.idx3-ubyte"
#define LABEL_TRAINING_DATA "../data/train-labels.idx1-ubyte"
#define LABEL_TETSTING_DATA "../data/t10k-labels.idx1-ubyte"

int main()
{
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

    // preprocess image
    std::vector<cv::Mat> preprocessImages = dataImages;

    // feature set extractor
    FeatureSetExtractor featureSetExtractor;
    featureSetExtractor.addFeature(new PixelExtractor(784));

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
    std::vector<int> hiddenLayers = {50};
    NeuralNetwork neuralNetwork(featureSetExtractor.getFeatureCount(), hiddenLayers);
    neuralNetwork.setMaxEpochs(300);
    neuralNetwork.setLearningMomentum(0.9);
    neuralNetwork.setLearningRate(0.001);
    neuralNetwork.setDesiredError(0.16);
    neuralNetwork.setTrainingType(StochasticTraining);

    int method;
    bool train = false;
    std::cout << "\nHay chon:"
              << "\n1. K Neareast Neighbor"
              << "\n2. Neural Network"
              << "\nYour choice:\t";
    std::cin >> method;
    Recognizer* recognizer;
    if (method == 1)
        recognizer = &kNearestNeighbors;
    else {
        recognizer = &neuralNetwork;

        int choice;
        std::cout << "\nHay chon: "
                  << "\n1. Train lai neural network"
                  << "\n2. Su dung model da train"
                  << "\nYour choid:\t";
        std::cin >> choice;

        train = (choice == 1);
    }

    // training and validating
    Validator validator;
    if (train || (method == 1))
        validator.validate(recognizer, inputs, outputs, 1);
    else
        recognizer = NeuralNetwork::deserialize();

    // user interaction
    // load data
    std::vector<cv::Mat> testingImages;
    const int TESTING_IMAGE_COUNT = 10000;
    testingImages.reserve(TESTING_IMAGE_COUNT);
    read_Mnist(IMAGE_TESTING_DATA, testingImages);

    std::vector<float> testingLabels(TESTING_IMAGE_COUNT);
    read_Mnist_Label(LABEL_TETSTING_DATA, testingLabels);

    std::vector<cv::Mat> preprocessedTestingImages = testingImages;
    std::vector<std::vector<val_type> > inputTesting, outputTesting;
    inputTesting.reserve(TESTING_IMAGE_COUNT);
    outputTesting.reserve(TESTING_IMAGE_COUNT);
    for (int i = 0; i < TESTING_IMAGE_COUNT; ++i) {
        inputTesting.push_back(featureSetExtractor.extractFeature(preprocessedTestingImages[i]));
        outputTesting.push_back({testingLabels[i]});
    }

    validator.run(recognizer, testingImages, inputTesting, outputTesting);

    if (method != 1 && train) {
        std::cout << "Do you want to save the network? <y/n>\t";
        char choice;
        std::cin >> choice;

        if (choice == 'y') {
            NeuralNetwork* nn = dynamic_cast<NeuralNetwork*>(recognizer);
            nn->serialize();
        }
    } else if (method != 1 && !train)
        // clean up
        delete recognizer;

    return 0;
}


