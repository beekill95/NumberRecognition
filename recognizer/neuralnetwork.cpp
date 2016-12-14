#include "neuralnetwork.h"

#include <cstring>
#include <iostream>
#include <cmath>

NeuralNetwork::NeuralNetwork(int numInputs, const std::vector<int> &hiddenLayers)
{
    // the default of output layer size is always 10
    // because there are 10 labels (0 .. 9)
    // and each label corresponds to an array
    // which has the highest probability of 1 at label index, and the rest is 0
    // for example:
    // the label is 4 => array is: (0, 0, 0, 0, 1, 0, 0, 0, 0, 0)
    if (hiddenLayers.size() != 0)
        neuralNetwork = new snn(numInputs, OutputLayerSize, hiddenLayers.size(), &hiddenLayers.at(0));
    else
        // hiddenLayers' size = 0
        neuralNetwork = new snn(numInputs, OutputLayerSize, 0, 0);

    // this is a classification problem
    neuralNetwork->setCostFunction(CrossEntropy);

    // set the default parameter
    neuralNetwork->setDesiredError(0.20);
    neuralNetwork->setLearningRate(0.09);
    neuralNetwork->setLearningMomentum(0.0);
    neuralNetwork->setMaxEpochs(100);
    neuralNetwork->setTrainingType(BatchTraining);
}

NeuralNetwork::~NeuralNetwork()
{
    delete neuralNetwork;
}

void NeuralNetwork::train(const std::vector<std::vector<val_type> > &inputs, const std::vector<std::vector<val_type> > &outputs)
{
    // check whether the inputs and outputs has the same size
    if (inputs.size() != outputs.size() || outputs[0].size() != 1)
        return;

    // convert the inputs, outputs to snnMatrix
    snnMatrix inputData(inputs.size(), inputs[0].size());
    snnMatrix outputData(outputs.size(), OutputLayerSize);

    val_type tmp[OutputLayerSize];
    for (size_t i = 0; i < inputs.size(); ++i) {
        // need to check
        // whether this is zero initialized
        memset(tmp, 0, OutputLayerSize * sizeof(val_type));
        tmp[(int)(outputs[i][0])] = 1.0;

        inputData.setRow(i, inputs.at(i));
        outputData.setRow(i, OutputLayerSize, tmp);
    }

    // kiem tra lai xem co so nao la nan hoac -nan
//    for (size_t i = 0; i < inputs.size(); ++i) {
//        const val_type* inputRow = inputData.row(i);
//        const val_type* outputRow = outputData.row(i);

//        for (int j = 0; j < inputData.getCols(); ++j)
//            if (std::isnan(inputRow[j]))
//                std::cout << "Loi o Input dong " << i << " cot " << j << '\n';

//        for (int j = 0; j < outputData.getCols(); ++j)
//            if (std::isnan(outputRow[j]))
//                std::cout << "Loi o Output dong " << i << " cot " << j << '\n';
//    }

    // begin training
    neuralNetwork->train(&inputData, &outputData);
}

std::vector<val_type> NeuralNetwork::predict(const std::vector<val_type> &input) const
{
    val_type outputResult[OutputLayerSize];
    neuralNetwork->predict(&input.at(0), outputResult);

    val_type label = 0;
    val_type max = outputResult[0];
    for (int i = 1; i < OutputLayerSize; ++i)
        if (outputResult[i] > max) {
            max = outputResult[i];
            label = i;
        }

    return {label};
}
