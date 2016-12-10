#ifndef SNNDATA
#define SNNDATA

typedef double snn_type;

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

    const snn_type* row(int index) const;
    snn_type* row(int index);

    const snn_type& at(int r, int c) const;
    snn_type& at(int r, int c);
};

#endif // SNNDATA

