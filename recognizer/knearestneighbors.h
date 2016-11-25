#ifndef KNEARESTNEIGHBORS_H
#define KNEARESTNEIGHBORS_H

#include "recognizer.h"

class KNearestNeighbors : public Recognizer
{
private:
    int k_neighbors;

    std::vector<std::vector<double> > inputs;
    std::vector<std::vector<double> > outputs;

public:
    KNearestNeighbors(int k_neighbors);
    ~KNearestNeighbors();

    void train(const std::vector<std::vector<double> > &inputs, const std::vector<std::vector<double> > &outputs) override;
    std::vector<double> predict(const std::vector<double> &input) override;
};

#endif // KNEARESTNEIGHBORS_H
