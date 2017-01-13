#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "recognizer/recognizer.h"
#include "definition.h"

#include <vector>
#include <opencv2/core/core.hpp>

class Validator
{
private:
    static const float DEFAULT_TRAINING_PERCENTAGE;

public:
    Validator();

    void validate(Recognizer* recognizer,
                  const std::vector<std::vector<val_type> >& inputs,
                  const std::vector<std::vector<val_type> >& outputs,
                  float trainingPercentage = 0.8f) const;
    void run(Recognizer* Recognizer,
             const std::vector<cv::Mat>& images,
             const std::vector<std::vector<val_type> >& inputs,
             const std::vector<std::vector<val_type> >& outputs) const;
};

#endif // VALIDATOR_H
