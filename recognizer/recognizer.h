#ifndef RECOGNIZER
#define RECOGNIZER

#include <vector>
#include "definition.h"

class Recognizer
{
public:
    virtual ~Recognizer() { }

    virtual void train(const std::vector<std::vector<val_type> >& inputs, const std::vector<std::vector<val_type> >& outputs) = 0;
    virtual std::vector<val_type> predict(const std::vector<val_type>& input) const = 0;
};

#endif // RECOGNIZER

