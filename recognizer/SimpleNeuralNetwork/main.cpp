#include <iostream>
#include <cmath>

#include "snn.h"
#include "snndata.h"

void simpleTest(int size)
{
    // simple test
    snnMatrix input(size, 1);
    snnMatrix output(size, 1);

//    input.at(0, 0) = 0.0; /*input.at(0, 1) = 0.0; */output.at(0, 0) = 0.0;
//    input.at(1, 0) = 0.25; /*input.at(1, 1) = 1.0; */output.at(1, 0) = 0.25;
//    input.at(2, 0) = 0.5; /*input.at(2, 1) = 0.0; */output.at(2, 0) = 0.5;
//    input.at(3, 0) = 1.0; /*input.at(3, 1) = 1.0; */output.at(3, 0) = 1.0;
//    input.at(4, 0) = 0.75; output.at(4, 0) = 0.75;


    float step = 1.0 / size;
    float curr = 0.0;
    for (int i = 0; i < size; ++i) {
        input.at(i, 0) = curr;
        output.at(i, 0) = curr;

        curr += step;
    }

//    int hiddens[] = {3};
    snn neuralNetwork(1, 1, 0, 0);
    neuralNetwork.setMaxEpochs(100);
    //neuralNetwork.setTrainingType(StochasticTraining);
    neuralNetwork.train(&input, &output);

    float* out = new float[1];
    for (int i = 0; i < size; ++i) {
        neuralNetwork.predict(input.row(i), out);

        float diff = out[0] - output.at(i, 0);
        std::cout << "Network result: " << out[0]
                  << "\tReal result: " << output.at(i, 0)
                  << "\tDifference is: " << fabs(diff) << '\n';
    }
    delete[] out;
}

void xorTest()
{
    // simple test
    snnMatrix input(4, 2);
    snnMatrix output(4, 1);

    input.at(0, 0) = 0.0; input.at(0, 1) = 0.0; output.at(0, 0) = 0.0;
    input.at(1, 0) = 0.0; input.at(1, 1) = 1.0; output.at(1, 0) = 1.0;
    input.at(2, 0) = 1.0; input.at(2, 1) = 0.0; output.at(2, 0) = 1.0;
    input.at(3, 0) = 1.0; input.at(3, 1) = 1.0; output.at(3, 0) = 0.0;


    int hiddens[] = {3};
    snn neuralNetwork(2, 1, 1, hiddens);
    neuralNetwork.setMaxEpochs(500000);
    neuralNetwork.setDesiredError(0.0001);
    neuralNetwork.setLearningMomentum(0.2);
    neuralNetwork.setTrainingType(BatchTraining);
    neuralNetwork.train(&input, &output);

    float* out = new float[1];
    for (int i = 0; i < 4; ++i) {
        neuralNetwork.predict(input.row(i), out);

        float diff = out[0] - output.at(i, 0);
        std::cout << "Network result: " << out[0]
                  << "\tReal result: " << output.at(i, 0)
                  << "\tDifference is: " << fabs(diff) << '\n';
    }
    delete[] out;
}

void simpleClassificationTest(int size)
{
    // the rule is:
    // if x >= 5 => yA = 1, yB = 0
    // if x < 5 => yA = 0, yB = 1

    snnMatrix inputs(size, 1);
    snnMatrix outputs(size, 2);

//    inputs.at(0, 0) = 5.2; outputs.at(0, 0) = 1.0; outputs.at(0, 1) = 0.0;
//    inputs.at(1, 0) = 4.3; outputs.at(1, 0) = 0.0; outputs.at(1, 1) = 1.0;
//    inputs.at(2, 0) = 5.1; outputs.at(2, 0) = 1.0; outputs.at(2, 1) = 0.0;
//    inputs.at(3, 0) = 4.8; outputs.at(3, 0) = 0.0; outputs.at(3, 1) = 1.0;

    for (int i = 0; i < size; ++i) {
        float val = 1.0 * rand() / RAND_MAX;

        inputs.at(i, 0) = val;

        outputs.at(i, 0) = (val > 0.5) ? 1.0 : 0.0;
        outputs.at(i, 1) = (val > 0.5) ? 0.0 : 1.0;
    }

    int hiddens[] = {3};
    snn neuralNetwork(1, 2, 1, hiddens);
    neuralNetwork.setCostFunction(CrossEntropy);
    neuralNetwork.setMaxEpochs(1000);
    neuralNetwork.setDesiredError(0.1);
    neuralNetwork.setTrainingType(BatchTraining);
    neuralNetwork.train(&inputs, &outputs);

    float* out = new float[2];
    for (int i = 0; i < size; ++i) {
        neuralNetwork.predict(inputs.row(i), out);

        char a = (out[0] > out[1]) ? 'A' : 'B';
        char exp = (inputs.at(i, 0) > 0.5) ? 'A' : 'B';

        std::cout << "Predict: " << a << "\tExpected: " << exp << '\n';
    }
    delete[] out;
}

void circleClassificationTest(int size)
{
    // the rule is:
    // if ||x1, x2|| < 0.5 => class A
    // otherwise => class B

    snnMatrix inputs(size, 2);
    snnMatrix outputs(size, 2);

//    inputs.at(0, 0) = 5.2; outputs.at(0, 0) = 1.0; outputs.at(0, 1) = 0.0;
//    inputs.at(1, 0) = 4.3; outputs.at(1, 0) = 0.0; outputs.at(1, 1) = 1.0;
//    inputs.at(2, 0) = 5.1; outputs.at(2, 0) = 1.0; outputs.at(2, 1) = 0.0;
//    inputs.at(3, 0) = 4.8; outputs.at(3, 0) = 0.0; outputs.at(3, 1) = 1.0;

    for (int i = 0; i < size; ++i) {
        float val1 = 1.0 * rand() / RAND_MAX;
        float val2 = 1.0 * rand() / RAND_MAX;

        inputs.at(i, 0) = val1;
        inputs.at(i, 1) = val2;

        float dist = sqrt(val1 * val1 + val2 * val2);

        outputs.at(i, 0) = (dist < 0.5) ? 1.0 : 0.0;
        outputs.at(i, 1) = (dist < 0.5) ? 0.0 : 1.0;
    }

    int hiddens[] = {3};
    snn neuralNetwork(2, 2, 1, hiddens);
    neuralNetwork.setCostFunction(CrossEntropy);
    neuralNetwork.setMaxEpochs(1000);
    neuralNetwork.setDesiredError(0.16);
    neuralNetwork.setTrainingType(BatchTraining);
    neuralNetwork.train(&inputs, &outputs);

    float* out = new float[2];
    for (int i = 0; i < size; ++i) {
        neuralNetwork.predict(inputs.row(i), out);

        char a = (out[0] > out[1]) ? 'A' : 'B';

        char exp = (outputs.at(i, 0) == 1.0) ? 'A' : 'B';

        std::cout << "Predict: " << a << "\tExpected: " << exp << '\n';
    }
    delete[] out;
}

void circleWithNoiseClassificationTest(int size)
{
    // the rule is:
    // if ||x1, x2|| < 0.5 => class A
    // otherwise => class
    snnMatrix inputs(size, 2);
    snnMatrix outputs(size, 2);

//    inputs.at(0, 0) = 5.2; outputs.at(0, 0) = 1.0; outputs.at(0, 1) = 0.0;
//    inputs.at(1, 0) = 4.3; outputs.at(1, 0) = 0.0; outputs.at(1, 1) = 1.0;
//    inputs.at(2, 0) = 5.1; outputs.at(2, 0) = 1.0; outputs.at(2, 1) = 0.0;
//    inputs.at(3, 0) = 4.8; outputs.at(3, 0) = 0.0; outputs.at(3, 1) = 1.0;

    for (int i = 0; i < size; ++i) {
        float val1 = 1.0 * rand() / RAND_MAX;
        float val2 = 1.0 * rand() / RAND_MAX;
        float noise = (1.0 * rand() / RAND_MAX) / 5  - 1.0 / 10;

        inputs.at(i, 0) = val1 + noise;
        inputs.at(i, 1) = val2 + noise;

        float dist = sqrt(val1 * val1 + val2 * val2);

        outputs.at(i, 0) = (dist < 0.5) ? 1.0 : 0.0;
        outputs.at(i, 1) = (dist < 0.5) ? 0.0 : 1.0;
    }

    int hiddens[] = {3, 5};
    snn neuralNetwork(2, 2, 2, hiddens);
    neuralNetwork.setCostFunction(CrossEntropy);
    neuralNetwork.setMaxEpochs(1000);
    neuralNetwork.setDesiredError(0.20);
    neuralNetwork.setTrainingType(BatchTraining);
    neuralNetwork.train(&inputs, &outputs);

    float* out = new float[2];
    for (int i = 0; i < size; ++i) {
        neuralNetwork.predict(inputs.row(i), out);

        char a = (out[0] > out[1]) ? 'A' : 'B';

        char exp = (outputs.at(i, 0) == 1.0) ? 'A' : 'B';

        std::cout << "Predict: " << a << "\tExpected: " << exp << '\n';
    }
    delete[] out;
}

int main()
{
    circleWithNoiseClassificationTest(20);
//    circleClassificationTest(50);
//    simpleClassificationTest(50);
//    xorTest();
//    simpleTest(10);
    return 0;
}
