#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "recognizer/recognizer.h"
#include "definition.h"

#include "vector"

class Validator
{
private:
    static const float DEFAULT_TRAINING_PERCENTAGE;

public:
    Validator();

    void validate(Recognizer* recognizer,
                  const std::vector<std::vector<val_type> >& inputs,
                  const std::vector<std::vector<val_type> >& outputs,
                  float trainingPercentage = 0.8f);
};

#endif // VALIDATOR_H
