#ifndef SNNDATA
#define SNNDATA

#include <vector>
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>

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
    MiniBatchTraining,
    Rprop
};

class snnMatrix
{
private:
    int _rows, _cols;
    snn_type* _data;

public:
    snnMatrix(int rows, int cols);
    snnMatrix(int rows, int cols, snn_type* data);
    snnMatrix(const snnMatrix& other);
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

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(_rows, _cols);
    //        archive(cereal::binary_data(_data, sizeof(snn_type) * _rows * _cols));
        for (int i = 0; i < _rows * _cols; ++i)
            archive(_data[i]);
    }

    template<class Archive>
    static void load_and_construct(Archive& archive, cereal::construct<snnMatrix>& construct)
    {
        int rows, cols;
        snn_type* data;

        archive(rows, cols);
        data = new snn_type[rows * cols];
        for (int i = 0; i < rows * cols; ++i)
            archive(data[i]);

        construct(rows, cols, data);
    }
};

#endif // SNNDATA

