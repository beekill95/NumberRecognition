#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "recognizer/recognizer.h"
#include "vector"

class Validator
{
private:
    static const float DEFAULT_TRAINING_PERCENTAGE;

public:
    Validator();

    void validate(Recognizer* recognizer,
                  const std::vector<std::vector<double> >& inputs,
                  const std::vector<std::vector<double> >& outputs,
                  float trainingPercentage = 0.8f);
};

#endif // VALIDATOR_H
