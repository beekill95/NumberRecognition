#include "snnlayer.h"

#include <cstring>
#include <cmath>
#include <random>
#include <iostream>

#include "snnfunction.h"

#define random_0_1 (rand() / (snn_type) RAND_MAX)

snnLayer::snnLayer(int prevLayerPerceptronCount, int perceptronCount)
    : _prevLayerPerceptronCount(prevLayerPerceptronCount),
      _perceptronCount(perceptronCount),
      _activationFunction(Sigmoid),

      _learningRate(0.5),
      _learningMomentum(0.0),

      // each row is a perceptron
      // each column in each row is a weight of connection to previous layer
      // the plus 1 is for bias
      _weights(perceptronCount, prevLayerPerceptronCount + 1),

      // each weights has an error
      _delaWeigths(perceptronCount, prevLayerPerceptronCount + 1),
      _prevDeltaWeights(perceptronCount, prevLayerPerceptronCount + 1)
{
    _inputs = new snn_type[prevLayerPerceptronCount];
    memset(_inputs, 0, prevLayerPerceptronCount * sizeof(snn_type));
//    std::fill(_inputs, _inputs + prevLayerPerceptronCount, (snn_type) 0.0);

    _outputs = new snn_type[perceptronCount];
    memset(_outputs, 0, perceptronCount * sizeof(snn_type));
//    std::fill(_outputs, _outputs + perceptronCount, (snn_type) 0.0);
}

snnLayer::snnLayer(
        int prevLayerPerceptronCount,
        int perceptronCount,
        snn_activation_function activationFunction,
        snn_type learningRate,
        snn_type learningMomentum,
        const snnMatrix &weights,
        const snnMatrix &deltaWeights,
        const snnMatrix &prevDeltaWeights,
        snn_type *inputs,
        snn_type *output)
    : _prevLayerPerceptronCount(prevLayerPerceptronCount),
      _perceptronCount(perceptronCount),
      _activationFunction(activationFunction),
      _learningRate(learningRate),
      _learningMomentum(learningMomentum),
      _weights(weights),
      _delaWeigths(deltaWeights),
      _prevDeltaWeights(prevDeltaWeights),
      _inputs(inputs),
      _outputs(output)
{ }

snnLayer::snnLayer(const snnLayer &other)
    : _prevLayerPerceptronCount(other._prevLayerPerceptronCount),
      _perceptronCount(other._perceptronCount),
      _activationFunction(other._activationFunction),
      _learningRate(other._learningRate),
      _learningMomentum(other._learningMomentum),
      _weights(other._weights),
      _delaWeigths(other._delaWeigths),
      _prevDeltaWeights(other._prevDeltaWeights)
{
    _inputs = new snn_type[_prevLayerPerceptronCount];
    memcpy(_inputs, other._inputs, sizeof(snn_type) * _prevLayerPerceptronCount);

    _outputs = new snn_type[_perceptronCount];
    memcpy(_outputs, other._outputs, sizeof(snn_type) * _perceptronCount);
}

snnLayer::~snnLayer()
{
    delete[] _inputs;
    delete[] _outputs;
}

void snnLayer::_resetOutputs()
{
    memset(_outputs, 0, _perceptronCount * sizeof(snn_type));
//    std::fill(_outputs, _outputs + _perceptronCount, (snn_type) 0.0);
}

void snnLayer::_resetDeltaWeights()
{
    for (int i = 0; i < _perceptronCount; ++i) {
        snn_type* deltaWeights = _delaWeigths.row(i);

        memset(deltaWeights, 0, (_prevLayerPerceptronCount + 1) * sizeof(snn_type));
//        std::fill(deltaWeights, deltaWeights + _prevLayerPerceptronCount + 1, (snn_type) 0.0);
    }
}

void snnLayer::calculateOutputs(const snn_type *inputs)
{
    // reset output
    _resetOutputs();

    // copy the input to store
    memcpy(_inputs, inputs, _prevLayerPerceptronCount * sizeof(snn_type));

    // calculate the output of this layer
    for (int perceptron = 0; perceptron < _perceptronCount; ++perceptron) {
        const snn_type* thisPerceptronWeights = _weights.row(perceptron);

        snn_type sum = 0.0;
        for (int i = 0; i < _prevLayerPerceptronCount; ++i)
            sum += thisPerceptronWeights[i] * inputs[i];

        // bias
        // the bias is always at the last column of the array of weights
        sum += thisPerceptronWeights[_prevLayerPerceptronCount];

        // apply activation function
        switch(_activationFunction) {
        case Sigmoid:
//            std::cout << "\n\nsum is " << sum << "\nsigmoid is " << sigmoid_func(sum);
            _outputs[perceptron] = sigmoid_func(sum);
            break;
        default:
            break;
        }
    }
}

const snn_type* snnLayer::getOutputs() const
{
    return _outputs;
}

void snnLayer::applyDeltaWeights()
{
    for (int i = 0; i < _perceptronCount; ++i) {
        const snn_type* deltaWeights = _delaWeigths.row(i);
        snn_type* weights = _weights.row(i);

        // apply delta weights to current weights
        for (int j = 0; j < _prevLayerPerceptronCount + 1; ++j)
            weights[j] -= _learningRate * deltaWeights[j];
    }

    _resetDeltaWeights();
}

// currently using MSE + Sigmoid
void snnLayer::updateDeltaWeights(const snn_type *errors)
{
    for (int perceptron = 0; perceptron < _perceptronCount; ++perceptron) {
        snn_type perceptronError = errors[perceptron];
        snn_type perceptronOutput = _outputs[perceptron];

        if (std::isnan(errors[perceptron]) || std::isinf(errors[perceptron])) {
            int x = 0;
            x += 1;
            std::cout << "x : " << x;
        }

        snn_type* prevPerceptronDeltaWeights = _prevDeltaWeights.row(perceptron);
        snn_type* perceptronDeltaWeights = _delaWeigths.row(perceptron);

        if (_activationFunction == Sigmoid) {
            // not including bias
            for (int w = 0; w < _prevLayerPerceptronCount; ++w) {
                snn_type previousDeltaWeight = prevPerceptronDeltaWeights[w];
                snn_type deltaWeight = perceptronError * sigmoid_deri_func(perceptronOutput) * _inputs[w];

                // current delta weights
                perceptronDeltaWeights[w] += previousDeltaWeight * _learningMomentum + deltaWeight;

                // store previous delta weights
                prevPerceptronDeltaWeights[w] = deltaWeight;
            }

            // calculating deltaweights for bias
            {
                snn_type previousDeltaWeight = prevPerceptronDeltaWeights[_prevLayerPerceptronCount];
                snn_type deltaWeight = perceptronError * sigmoid_deri_func(perceptronOutput);

                // current delta weight
                perceptronDeltaWeights[_prevLayerPerceptronCount] += previousDeltaWeight * _learningMomentum + deltaWeight;

                // store previous delta weight
                prevPerceptronDeltaWeights[_prevLayerPerceptronCount] = deltaWeight;
            }
        }
    }
}

void snnLayer::generateRandomWeights(snn_type minimum, snn_type maximum)
{
    for (int perceptron = 0; perceptron < _perceptronCount; ++perceptron) {
        snn_type* weights = _weights.row(perceptron);

        for (int w = 0; w < _prevLayerPerceptronCount + 1; ++w)
            weights[w] = random_0_1 * (maximum - minimum) + minimum;
    }
}

void snnLayer::propagateErrors(const snn_type *errors, snn_type *propagatedErrors) const
{
    // reset propagated error
    memset(propagatedErrors, 0, _prevLayerPerceptronCount * sizeof(snn_type));
//    std::fill(propagatedErrors, propagatedErrors + _prevLayerPerceptronCount, (snn_type) 0.0);

    for (int i = 0; i < _perceptronCount; ++i) {
        const snn_type* thisPerceptronWeights = _weights.row(i);

        for (int j = 0; j < _prevLayerPerceptronCount; ++j)
            propagatedErrors[j] += thisPerceptronWeights[j] * errors[i];
    }
}

