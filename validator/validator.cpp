#include "validator.h"
#include <cassert>
#include <iostream>

const float Validator::DEFAULT_TRAINING_PERCENTAGE  = 0.8f;

Validator::Validator()
{ }

void Validator::validate(Recognizer *recognizer,
                         const std::vector<std::vector<double> > &inputs,
                         const std::vector<std::vector<double> > &outputs,
                         float trainingPercentage)
{
    if (inputs.size() != outputs.size())
        return;

    if (trainingPercentage > 1.0f || trainingPercentage < 0.0f)
        trainingPercentage = DEFAULT_TRAINING_PERCENTAGE;

    // divide the training / testing
    std::vector<std::vector<double> > trainingImages, testingImages;
    std::vector<std::vector<double> > trainingLabels, testingLabels;

    int trainingDataCount = (int) (inputs.size() * trainingPercentage);
    int testingDataCount = inputs.size() - trainingDataCount;


    trainingImages.reserve(trainingDataCount);
    trainingLabels.reserve(trainingDataCount);
    testingImages.reserve(testingDataCount);
    testingImages.reserve(testingDataCount);
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        if (i < trainingDataCount) {
            trainingImages.push_back(inputs[i]);
            trainingLabels.push_back(outputs[i]);
        } else {
            testingImages.push_back(inputs[i]);
            testingLabels.push_back(outputs[i]);
        }
    }

    // training
    recognizer->train(trainingImages, trainingLabels);

    // validate ket qua
    std::vector<std::vector<double> > results;
    results.reserve(testingDataCount);
    for (std::size_t i = 0; i < testingImages.size(); ++i) {
        std::cout << "\nPredicting #" << i << " ...";
        results.push_back(recognizer->predict(testingImages[i]));
    }

    // check result
    assert(results.size() == testingLabels.size());
    int rightCount = 0;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i] == testingLabels[i])
            ++rightCount;

    }

    // display the result
    std::cout << "Phan loai dung: " << rightCount << " truong hop trong tong so " << testingLabels.size() << " truong hop"
              << "\nPhan loai dung: " << rightCount * 100.0f / testingLabels.size() << " %" << std::endl;
}

