#ifndef KNEARESTNEIGHBORS_H
#define KNEARESTNEIGHBORS_H

#include "recognizer.h"

class KNearestNeighbors : public Recognizer
{
private:
    int k_neighbors;

    std::vector<std::vector<val_type> > inputs;
    std::vector<std::vector<val_type> > outputs;

public:
    KNearestNeighbors(int k_neighbors);
    ~KNearestNeighbors();

    void train(const std::vector<std::vector<val_type> > &inputs, const std::vector<std::vector<val_type> > &outputs) override;
    std::vector<val_type> predict(const std::vector<val_type> &input, bool verbose = false) const override;
};

#endif // KNEARESTNEIGHBORS_H
