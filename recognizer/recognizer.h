#ifndef RECOGNIZER
#define RECOGNIZER

#include <vector>

class Recognizer
{
public:
    virtual ~Recognizer() { }

    virtual void train(const std::vector<std::vector<double> >& inputs, const std::vector<std::vector<double> >& outputs) = 0;
    virtual std::vector<double> predict(const std::vector<double>& input) = 0;
};

#endif // RECOGNIZER

