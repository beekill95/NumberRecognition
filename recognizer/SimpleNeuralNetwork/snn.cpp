#include "snn.h"

#include "snnfunction.h"

#include <cmath>
#include <cstring>
#include <random>
#include <ctime>

#ifdef VERBOSE
#include <iostream>
#endif

snn::snn(int numInputs, int numOutputs, int numHiddenLayers, const int* nodesPerLayer)
    : _numInputs(numInputs),
      _numLayers(numHiddenLayers + 1),
      _costFunction(MeanSquareError),
      _trainingType(BatchTraining),
      _maxEpochs(300),
      _batchSize(10),
      _desiredMeanError(0.001)
{
    // generate layers
    _layers = new snnLayer*[_numLayers];
    for (int i = 0; i < _numLayers; ++i) {
        int prevLayerPerceptron;
        int currLayerPerceptron;

        if (i == 0)
            // first layer of hidden layer or output layer
            prevLayerPerceptron = numInputs;
        else
            // other layers
            prevLayerPerceptron = nodesPerLayer[i - 1];

        if (i == _numLayers - 1)
            // output layer
            currLayerPerceptron = numOutputs;
        else
            // other layers
            currLayerPerceptron = nodesPerLayer[i];

        // generate current layer
        _layers[i] = new snnLayer(prevLayerPerceptron, currLayerPerceptron);
    }
}

snn::~snn()
{
    for (int i = 0; i < _numLayers; ++i)
        delete _layers[i];
    delete[] _layers;
}

void snn::_generateRandomWeights()
{
    srand(time(0));
    for (int i = 0; i < _numLayers; ++i)
        _layers[i]->generateRandomWeights(-10, 10);
}

void snn::predict(const snn_type *inputs, snn_type *outputs) const
{
    _feedForward(inputs, outputs);
}

void snn::train(const snnMatrix *inputs, const snnMatrix *outputs)
{
    // perform checking
    if (_numInputs != inputs->getCols()
            || inputs->getRows() != outputs->getRows()
            || outputs->getCols() != _layers[_numLayers - 1]->getPerceptronCount())
        return;

    // generate random weights for all weights matrix
    _generateRandomWeights();

    snn_type* networkOutputs = new snn_type[outputs->getCols()];
    snn_type* outputErrors = new snn_type[outputs->getCols()](); //<-- () : zero initialized

    // using for minibatch training
    int inputFeeded = 0;

    for (int epoch = 0; epoch < _maxEpochs; ++epoch) {
        snn_type sumError = 0;

        for (int r = 0; r < inputs->getRows(); ++r) {
            const snn_type* input = inputs->row(r);
//            memset(networkOutputs, 0, sizeof(snn_type) * outputs->getCols());
            std::fill(networkOutputs, networkOutputs + outputs->getCols(), (snn_type) 0.0);

            // feed forward phase
            _feedForward(input, networkOutputs);

            // calculate error
            sumError += _calculateOutputErrors(outputs->row(r), networkOutputs, outputErrors);

            // backpropagate
            _backPropagation(outputErrors);

            // apply delta weights
            switch (_trainingType) {
            case StochasticTraining:
                _applyDeltaWeights();
                break;
            case BatchTraining:
                if (r == inputs->getRows() - 1)
                    _applyDeltaWeights();
                break;
            case MiniBatchTraining:
                if (inputFeeded == _batchSize) {
                    _applyDeltaWeights();
                    inputFeeded = 0;
                } else
                   ++inputFeeded;
                break;
            }
        }

        // check for error below the desired error
        // sumError may suffer from overflow
#ifdef VERBOSE
        std::cout << "Epochs: " << epoch << "\tCurrent error: " << sumError / outputs->getRows() << '\n';
#endif

        if (sumError / outputs->getRows() < _desiredMeanError)
            break;
    }

    // cleaning up
    delete[] networkOutputs;
    delete[] outputErrors;
}

void snn::_feedForward(const snn_type *inputs, snn_type *outputs) const
{
    for (int i = 0; i < _numLayers; ++i) {
        if (i == 0)
            // first layer
            _layers[0]->calculateOutputs(inputs);
        else {
            // other layers
            const snn_type* inputs = _layers[i - 1]->getOutputs();
            _layers[i]->calculateOutputs(inputs);
        }
    }

    // copy the output to the outputs pointer
    if (outputs != 0) {
        int outputLayerPerceptronCount = _layers[_numLayers - 1]->getPerceptronCount();
        const snn_type* outputOfLastLayer = _layers[_numLayers - 1]->getOutputs();

        if (_costFunction == CrossEntropy) {
            // using softmax function
            // to normalize the result to 0 - 1
            // satisfies sigma (output) = 1
            snn_type sum = 0;

            // first pass to calculate the sum
            for (int i = 0; i < outputLayerPerceptronCount; ++i)
                sum += exp(outputOfLastLayer[i]);

            // second pass to calculate the probability
            // of belonging to one class
            for (int i = 0; i < outputLayerPerceptronCount; ++i) {
                outputs[i] = softmax_func(outputOfLastLayer[i], sum);
//#ifdef VERBOSE
//                std::cout << "Output [" << i << "]: " << outputs[i] << '\t';
//#endif
            }
//#ifdef VERBOSE
//            std::cout << '\n';
//#endif
        } else if (_costFunction == MeanSquareError)
            memcpy(outputs, outputOfLastLayer, outputLayerPerceptronCount * sizeof(snn_type));
    }
}

void snn::_backPropagation(const snn_type *outputErrors)
{
    snn_type* currentErrors = 0;
    for (int i = _numLayers - 1; i >= 0; --i) {
        int beforeThisLayerPerceptronCount = _layers[i]->getPrevLayerPerceptronCount();

        if (i == _numLayers - 1) {
            // output layer
            _layers[i]->updateDeltaWeights(outputErrors);

            currentErrors = new snn_type[beforeThisLayerPerceptronCount];
            _layers[i]->propagateErrors(outputErrors, currentErrors);
        } else {
            snn_type* outputErrors = currentErrors;
            _layers[i]->updateDeltaWeights(outputErrors);

            currentErrors = new snn_type[beforeThisLayerPerceptronCount];
            _layers[i]->propagateErrors(outputErrors, currentErrors);
            delete[] outputErrors;
        }
    }

    if (currentErrors != 0)
        delete[] currentErrors;
}

//

snn_type snn::_calculateOutputErrors(const snn_type *expectedOutputs, const snn_type *networkOutputs, snn_type *errors) const
{
    snn_type sum = 0;
    int outputSize = _layers[_numLayers - 1]->getPerceptronCount();

    if (_costFunction == MeanSquareError) {
        for (int i = 0; i < outputSize; ++i) {
            snn_type expectedOutput = expectedOutputs[i];
            snn_type networkOutput = networkOutputs[i];

            sum += mean_square_error_func(expectedOutput, networkOutput);
            errors[i] = mean_square_error_deri_func(expectedOutput, networkOutput);

//            if (std::isnan(errors[i]) || std::isinf(errors[i])) {
//                int x = 0;
//                x += 1;
//            }
        }
    } else if (_costFunction == CrossEntropy) {
        for (int i = 0; i < outputSize; ++i) {
            snn_type expectedOutput = expectedOutputs[i];
            snn_type networkOutput = networkOutputs[i];

            sum += cross_entropy_func(expectedOutput, networkOutput);
            errors[i] = cross_entropy_deri_func(expectedOutput, networkOutput);
        }
    }

    return sum / outputSize;
}

void snn::_applyDeltaWeights()
{
    for (int l = 0; l < _numLayers; ++l)
        _layers[l]->applyDeltaWeights();
}
