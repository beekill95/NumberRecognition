#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "recognizer.h"
#include "snn.h"

class NeuralNetwork : public Recognizer
{
private:
    enum {
        OutputLayerSize = 10
    };
    snn* neuralNetwork;

public:
    // numInputs: the number of element in input vector
    // hiddenLayers: the number of perceptron in each hidden layer
    NeuralNetwork(int numInputs, const std::vector<int>& hiddenLayers);
    ~NeuralNetwork();

    // get / set learning rate
    double getLearningRate() const {return neuralNetwork->getLearningRate();}
    void setLearningRate(double learningRate) {neuralNetwork->setLearningRate(learningRate);}

    // get / set learning momentum
    double getLearningMomentum() const {return neuralNetwork->getLearningMomentum();}
    void setLearningMomentum(double learningMomentum) {neuralNetwork->setLearningMomentum(learningMomentum);}

    // get / set max epochs
    int getMaxEpochs() const {return neuralNetwork->getMaxEpochs();}
    void setMaxEpochs(int epochs) {neuralNetwork->setMaxEpochs(epochs);}

    // get / set desired error
    double getDesiredError() const {return neuralNetwork->getDesiredError();}
    void setDesiredError(double error) {neuralNetwork->setDesiredError(error);}

    // get / set training type
    snn_training_type getTrainingType() const {return neuralNetwork->getTrainingType();}
    void setTrainingType(snn_training_type trainingType) {neuralNetwork->setTrainingType(trainingType);}

    // get / set batch size
//    int getBatchSize() const {return neuralNetwork-}
    void setBatchSize(int batchSize) {neuralNetwork->setBatchSize(batchSize);}

    // train the network
    void train(const std::vector<std::vector<double> > &inputs, const std::vector<std::vector<double> > &outputs) override;

    // predict the result
    // the return is always a 1-element array
    // contains the label (0 .. 9) of the image
    std::vector<double> predict(const std::vector<double> &input) const override;
};

#endif // NEURALNETWORK_H
