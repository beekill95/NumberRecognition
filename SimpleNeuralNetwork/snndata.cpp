#include "snndata.h"

#include <cstring>
#include <cassert>

#ifdef VERBOSE
#include <iostream>
#endif

snnMatrix::snnMatrix(int rows, int cols, snn_type *data)
    : _rows(rows), _cols(cols), _data(data)
{ }

snnMatrix::snnMatrix(int rows, int cols)
    : _rows(rows), _cols(cols)
{
    _data = new snn_type[rows * cols];
    memset(_data, 0, rows * cols * sizeof(snn_type));
}

snnMatrix::snnMatrix(const snnMatrix &other)
    : _rows(other._rows), _cols(other._cols)
{
    _data = new snn_type[_rows * _cols];
    memcpy(_data, other._data, sizeof(snn_type) * _rows * _cols);
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

void snnMatrix::setRow(int rowIndex, int size, const snn_type *row)
{
    if (size != _cols || rowIndex < 0 || rowIndex >= _rows)
        return;

    snn_type* rowStart = _data + (rowIndex * _cols);
    memcpy(rowStart, row, _cols * sizeof(snn_type));
//#ifdef VERBOSE
//    int minOfTwo = (size > 5) ? 5 : size;
//    for (int i = 0; i < minOfTwo; ++i)
//        std::cout << rowStart[i] << ' ';
//    std::cout << std::endl;
//#endif
}

void snnMatrix::setRow(int rowIndex, const std::vector<snn_type> &row)
{
    if (_cols != (int) row.size() || rowIndex < 0 || rowIndex >= _rows)
        return;

    snn_type* rowStart = _data + (rowIndex * _cols);
    memcpy(rowStart, &row[0], _cols * sizeof(snn_type));
//#ifdef VERBOSE
//    int minOfTwo = (row.size() > 5) ? 5 : row.size();
//    for (int i = 0; i < minOfTwo; ++i)
//        std::cout << rowStart[i] << ' ';
//    std::cout << std::endl;
//#endif
}