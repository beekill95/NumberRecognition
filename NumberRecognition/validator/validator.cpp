#include "validator.h"
#include <cassert>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#ifdef TIME_PROFILING
#include <chrono>
#endif

const float Validator::DEFAULT_TRAINING_PERCENTAGE  = 0.8f;

Validator::Validator()
{ }

void Validator::validate(Recognizer *recognizer,
                         const std::vector<std::vector<val_type> > &inputs,
                         const std::vector<std::vector<val_type> > &outputs,
                         float trainingPercentage) const
{
    if (inputs.size() != outputs.size())
        return;

    if (trainingPercentage > 1.0f || trainingPercentage < 0.0f)
        trainingPercentage = DEFAULT_TRAINING_PERCENTAGE;

    // divide the training / testing
    std::vector<std::vector<val_type> > trainingImages, testingImages;
    std::vector<std::vector<val_type> > trainingLabels, testingLabels;

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

#ifdef TIME_PROFILING
    std::chrono::system_clock::time_point start, finish;

    using millis = std::chrono::milliseconds;
    using minutes = std::chrono::minutes;
    start = std::chrono::high_resolution_clock::now();
#endif

    // training
    recognizer->train(trainingImages, trainingLabels);

#ifdef TIME_PROFILING
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "\nRecognizer Training took "
                  << std::chrono::duration_cast<minutes>(finish - start).count()
                  << " minutes";
#endif

//    std::cout << "Traing Finish!\nNhap mot so de tiep tuc: ";
//    int x;
//    std::cin >> x;

    // validate ket qua
#ifdef TIME_PROFILING
    start = std::chrono::high_resolution_clock::now();
#endif
    std::vector<std::vector<val_type> > results;
    results.reserve(testingDataCount);
    for (std::size_t i = 0; i < testingImages.size(); ++i) {
        std::cout << "\nPredicting #" << i << " ...";
        results.push_back(recognizer->predict(testingImages[i]));
    }
#ifdef TIME_PROFILING
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "\nRecognizer Predicting took "
                  << std::chrono::duration_cast<millis>(finish - start).count()
                  << " milliseconds";
#endif

    // check result
    assert(results.size() == testingLabels.size());
    int rightCount = 0;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i] == testingLabels[i])
            ++rightCount;

    }

    // display the result
    std::cout << "\nPhan loai dung: " << rightCount << " truong hop trong tong so " << testingLabels.size() << " truong hop"
              << "\nPhan loai dung: " << rightCount * 100.0f / testingLabels.size() << " %" << std::endl;
}

void Validator::run(
        Recognizer *recognizer,
        const std::vector<cv::Mat>& images,
        const std::vector<std::vector<val_type> > &inputs,
        const std::vector<std::vector<val_type> > &outputs) const
{
    if (inputs.size() != outputs.size())
        return;

    // validate ket qua
#ifdef TIME_PROFILING
    std::chrono::system_clock::time_point start, finish;
    using millis = std::chrono::milliseconds;
    using minutes = std::chrono::minutes;

    start = std::chrono::high_resolution_clock::now();
#endif
    std::vector<std::vector<val_type> > results;
    results.reserve(outputs.size());
    for (std::size_t i = 0; i < outputs.size(); ++i) {
        std::cout << "\nPredicting #" << i << " ...";
        results.push_back(recognizer->predict(inputs[i]));
    }
#ifdef TIME_PROFILING
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "\nRecognizer Predicting took "
                  << std::chrono::duration_cast<millis>(finish - start).count()
                  << " milliseconds";
#endif

    // check result
    assert(results.size() == outputs.size());
    int rightCount = 0;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i] == outputs[i])
            ++rightCount;

    }

    // display the result
    std::cout << "\nPhan loai dung: " << rightCount << " truong hop trong tong so " << inputs.size() << " truong hop"
              << "\nPhan loai dung: " << rightCount * 100.0f / inputs.size() << " %" << std::endl;


    // manual run
    std::string userInput;
    bool stop = false;
    while (!stop) {
        std::cout << "Input index of image to test: (not a number to stop)\t";
        std::cin >> userInput;

        int index = -1;
        try {
            index = std::stoi(userInput);
        } catch (std::invalid_argument) {
            stop = true;
        }

        if (!stop) {
            if (index < 0 || index >= inputs.size())
               std::cout << "Index out of bound: " << inputs.size() << std::endl;
            else {
               std::vector<val_type> result = recognizer->predict(inputs[index], true);

               std::cout << "\nPredicted image is: " << (int) result[0] << std::endl;
               cv::imshow("Number", images[index]);
               cv::waitKey(0);
            }
        }
    }
}
