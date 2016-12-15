#ifndef SNNLAYER_H
#define SNNLAYER_H

#include "snndata.h"

class snnLayer
{
private:
    // not include bias
    int _prevLayerPerceptronCount;
    int _perceptronCount;

    // the activation function is used for all perceptron in this layer
    // default is Sigmoid
    snn_activation_function _activationFunction;

    // learning rate
    snn_type _learningRate;

    // learning momentum
    snn_type _learningMomentum;

    // this layer weights
    // with each row is the weights for each perceptron
    // the last column in each row is the bias value
    snnMatrix _weights;

    // the sum error of each perceptron in this layer
    // last column is the error for bias
    snnMatrix _delaWeigths;

    // store previous delta weights
    snnMatrix _prevDeltaWeights;

    // the input of this layer
    snn_type* _inputs;

    // the output of this layer given the above input
    snn_type* _outputs;

private:
    void _resetOutputs();
    void _resetDeltaWeights();

public:
    // prevLayerPerceptronCount: the number of perceptron exists in previous layer
    //                           but doesn't count the bias
    // perceptronCount:          the number of perceptron in this layer
    //                           but doesn't count the bias
    snnLayer(int prevLayerPerceptronCount, int perceptronCount);
    ~snnLayer();

    // calculate the output of current layer, given the inputs
    // inputs: the input of this layer
    void calculateOutputs(const snn_type* inputs);

    // get current outputs of this layer
    const snn_type* getOutputs() const;

    // calculate the update weigth for current layer
    // errors: current layer's errors
    void updateDeltaWeights(const snn_type* errors);

    // apply delta weights to the weight matrix of current layer
    // and also reset delta weights to zero
    void applyDeltaWeights();

    // generate random weight matrix
    void generateRandomWeights(snn_type minimum, snn_type maximum);

    // propagate the error of current layer back to previous layer
    // errors: current layer errors
    // propagatedErrors: errors propagated to before-this-layer layer
    //                   this should be allocated before being passed to the function
    void propagateErrors(const snn_type* errors, snn_type* propagatedErrors) const;

    // get and set current layer activation function
    snn_activation_function getActivationFunction() const {return _activationFunction;}
    void setActivationFunction(snn_activation_function func) {_activationFunction = func;}

    // get and set current layer learning rate
    snn_type getLearningRate() const {return _learningRate;}
    void setLearningRate(snn_type learningRate) {_learningRate = learningRate;}

    // get and set current layer learning momentum
    snn_type getLearningMomentum() const {return _learningMomentum;}
    void setLearningMomentum(snn_type learningMomentum) {_learningMomentum = learningMomentum;}

    // get current layer's perceptron count
    int getPerceptronCount() const {return _perceptronCount;}

    // get previous layer's perceptron count
    int getPrevLayerPerceptronCount() const {return _prevLayerPerceptronCount;}
};

#endif // SNNLAYER_H
