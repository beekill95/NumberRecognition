#include "snndata.h"

#include <cstring>
#include <cassert>

snnMatrix::snnMatrix(int rows, int cols)
    : _rows(rows), _cols(cols)
{
    _data = new snn_type[rows * cols];
    memset(_data, 0, rows * cols * sizeof(snn_type));
}

snnMatrix::~snnMatrix()
{
    delete[] _data;
}

const snn_type* snnMatrix::row(int index) const
{
    if (index < 0 || index >= _rows)
        return 0;

    return _data + index * _cols;
}

snn_type* snnMatrix::row(int index)
{
    if (index < 0 || index >= _rows)
        return 0;

    return _data + index * _cols;
}

const snn_type& snnMatrix::at(int r, int c) const
{
    assert(r >= 0 && r < _rows);
    assert(c >= 0 && c < _cols);

    return _data[r * _cols + c];
}

snn_type& snnMatrix::at(int r, int c)
{
    assert(r >= 0 && r < _rows);
    assert(c >= 0 && c < _cols);

    return _data[r * _cols + c];
}
