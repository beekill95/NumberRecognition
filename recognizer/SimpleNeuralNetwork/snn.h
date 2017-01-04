#ifndef SNN_H
#define SNN_H

#include "snnlayer.h"
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>
#include <memory>

class snn
{
private:
    // the number of elements in input vector
    int _numInputs;

    // the number of layers exists in the network
    // includes both hidden layers and output layer
    int _numLayers;

    // cost function
    // the default value is mean square error
    snn_cost_function _costFunction;

    // training type
    snn_training_type _trainingType;

    // max epochs
    int _maxEpochs;

    // determine the size of the batch
    // using in mini batch training
    int _batchSize;

    // determine the desired output error
    snn_type _desiredMeanError;

    // an array stores the layers (both hidden and output layers) of the network
    snnLayer** _layers;

private:
    // generate random weights for all layers
    void _generateRandomWeights();

    // feed forward
    // outputs must be initialized before being passed to the function
    void _feedForward(const snn_type* inputs, snn_type* outputs) const;

    // back propagation
    void _backPropagation(const snn_type* outputErrors);

    // calculate errors of the output layers
    // this is misleading
    // the errors actually the error of the cost function's derivative with respect to the input
    //
    // if the cost function is mse:
    //      1/2 * (yi - ti)^2 then dC/dy = yi - ti
    //
    // if the cost function is cross entropy
    // and we assume that the last layer using softmax function
    // with yi = e^zi / sigma(e^zi)
    //      ti * log(yi) then dC/dzi = yi - ti
    //
    // the return is the sum of cost function over all output
    snn_type _calculateOutputErrors(const snn_type* expectedOutputs, const snn_type* networkOutputs, snn_type* errors) const;

    // apply delta weights for all layers
    // it's also reset all delta weights to zero
    void _applyDeltaWeights();

public:
    // snn constructor
    // numInputs: number of elements in input vector
    // numOutputs: number of elements in output vector
    // numHiddenLayers: number of hidden layers exist in neural network
    // nodesPerLayer: an array stores number of nodes per hidden layer
    snn(int numInputs, int numOutputs, int numHiddenLayers, const int* nodesPerLayer);
    snn(
            int numInputs,
            int numLayers,
            snn_cost_function costFunction,
            snn_training_type trainingType,
            int maxEpochs,
            int batchSize,
            snn_type desiredMeanError,
            snnLayer** layers);
    snn(const snn& other);
    ~snn();

    // get set which cost function is used in the network
    snn_cost_function getCostFunction() const {return _costFunction;}
    void setCostFunction(snn_cost_function func) {_costFunction = func;}

    // get set max epochs
    int getMaxEpochs() const {return _maxEpochs;}
    void setMaxEpochs(int maxEpochs) {_maxEpochs = maxEpochs;}

    // get set training type
    snn_training_type getTrainingType() const {return _trainingType;}
    void setTrainingType(snn_training_type trainingType) {_trainingType = trainingType;}

    // get set learning rate
    snn_type getLearningRate() const {return _layers[0]->getLearningRate();}
    void setLearningRate(snn_type learningRate) {
        for (int i = 0; i < _numLayers; ++i)
            _layers[i]->setLearningRate(learningRate);
    }

    // get set learning momentum
    snn_type getLearningMomentum() const {return _layers[0]->getLearningMomentum();}
    void setLearningMomentum(snn_type learningMomentum) {
        for (int i = 0; i < _numLayers; ++i)
            _layers[i]->setLearningMomentum(learningMomentum);
    }

    // get set desired error
    snn_type getDesiredError() const {return _desiredMeanError;}
    void setDesiredError(snn_type desiredError) {_desiredMeanError = desiredError;}

    // get set batch size
    void setBatchSize(int batchSize) {_batchSize = batchSize;}

    // traing snn
    // inputs: set of input vectors
    // outputs: set of output vectors
    void train(const snnMatrix* inputs, const snnMatrix* outputs);

    // snn predict
    // inputs: set of input vectors
    // outputs: set of return output vectors
    // outputs must be initialized before being passed to the function
    void predict(const snn_type* inputs, snn_type* outputs) const;

    // serialize and deserialze
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(_numInputs);
        archive(_numLayers);
        archive(_costFunction);
        archive(_trainingType);
        archive(_maxEpochs);
        archive(_batchSize);
        archive(_desiredMeanError);
        for (int i = 0; i < _numLayers; ++i) {
            std::unique_ptr<snnLayer> layer{_layers[i]};
            archive(layer);
            layer.release();
        }
    }

    template<class Archive>
    static void load_and_construct(Archive& archive, cereal::construct<snn>& construct)
    {
        int numInputs, numLayers;
        snn_cost_function costFunction;
        snn_training_type trainingType;
        int maxEpochs, batchSize;
        snn_type desiredMeanError;
        snnLayer** layers;

        archive(numInputs, numLayers, costFunction, trainingType, maxEpochs, batchSize, desiredMeanError);
        layers = new snnLayer*[numLayers];
        for (int i = 0; i < numLayers; ++i) {
            std::unique_ptr<snnLayer> layer{nullptr};
            archive(layer);

            layers[i] = new snnLayer(*layer);
        }

        construct(numInputs, numLayers, costFunction, trainingType, maxEpochs, batchSize, desiredMeanError, layers);
    }
};

#endif // SNN_H
