#ifndef SNNDATA
#define SNNDATA

#include <vector>

typedef float snn_type;

enum snn_activation_function
{
    Sigmoid = 0
};

enum snn_cost_function
{
    MeanSquareError = 0,
    CrossEntropy
};

enum snn_training_type
{
    BatchTraining = 0,
    StochasticTraining,
    MiniBatchTraining
};

class snnMatrix
{
private:
    int _rows, _cols;
    snn_type* _data;

public:
    snnMatrix(int rows, int cols);
    ~snnMatrix();

    int getRows() const {return _rows;}
    int getCols() const {return _cols;}

    // the size of row must agree with internal matrix' col count
    void setRow(int rowIndex, int size, const snn_type* row);
    void setRow(int rowIndex, const std::vector<snn_type>& row);

    const snn_type* row(int index) const;
    snn_type* row(int index);

    const snn_type& at(int r, int c) const;
    snn_type& at(int r, int c);
};

#endif // SNNDATA

