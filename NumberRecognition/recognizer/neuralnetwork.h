#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "recognizer.h"
#include "SimpleNeuralNetwork/snn.h"

class NeuralNetwork : public Recognizer
{
private:
    enum {
        OutputLayerSize = 10
    };
    snn* neuralNetwork;

    NeuralNetwork(snn* neuralNetwork);

public:
    // numInputs: the number of element in input vector
    // hiddenLayers: the number of perceptron in each hidden layer
    NeuralNetwork(int numInputs, const std::vector<int>& hiddenLayers);
    ~NeuralNetwork();

    // get / set learning rate
    val_type getLearningRate() const {return neuralNetwork->getLearningRate();}
    void setLearningRate(val_type learningRate) {neuralNetwork->setLearningRate(learningRate);}

    // get / set learning momentum
    val_type getLearningMomentum() const {return neuralNetwork->getLearningMomentum();}
    void setLearningMomentum(val_type learningMomentum) {neuralNetwork->setLearningMomentum(learningMomentum);}

    // get / set max epochs
    int getMaxEpochs() const {return neuralNetwork->getMaxEpochs();}
    void setMaxEpochs(int epochs) {neuralNetwork->setMaxEpochs(epochs);}

    // get / set desired error
    val_type getDesiredError() const {return neuralNetwork->getDesiredError();}
    void setDesiredError(val_type error) {neuralNetwork->setDesiredError(error);}

    // get / set training type
    snn_training_type getTrainingType() const {return neuralNetwork->getTrainingType();}
    void setTrainingType(snn_training_type trainingType) {neuralNetwork->setTrainingType(trainingType);}

    // get / set batch size
//    int getBatchSize() const {return neuralNetwork-}
    void setBatchSize(int batchSize) {neuralNetwork->setBatchSize(batchSize);}

    // set callback
    void setCallback(snn_callback callback) {neuralNetwork->setCallback(callback);}

    // train the network
    void train(const std::vector<std::vector<val_type> > &inputs, const std::vector<std::vector<val_type> > &outputs) override;

    // predict the result
    // the return is always a 1-element array
    // contains the label (0 .. 9) of the image
    std::vector<val_type> predict(const std::vector<val_type> &input, bool verbose = false) const override;

    // serialize
    void serialize();
    static NeuralNetwork* deserialize();
};

#endif // NEURALNETWORK_H
