#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

matrix::matrix(const size_t &input_rows, const size_t &input_cols)
    : rows(input_rows), cols(input_cols)
{
    if (rows == 0 or cols == 0)
        throw zero_size{};
    elements = new double[rows * cols]();
}

matrix::matrix(const vector<double> &input_elements)
    : rows(input_elements.size()), cols(input_elements.size())
{
    if (rows == 0)
        throw zero_size{};
    elements = new double[rows * cols]();
    for (size_t i{0}; i < rows; i++)
        elements[(rows * i) + i] = input_elements[i];
}

matrix::matrix(const size_t &input_rows, const size_t &input_cols, const vector<double> &input_elements)
    : rows(input_rows), cols(input_cols)
{
    if (rows == 0 or cols == 0)
        throw zero_size{};
    if (input_elements.size() != rows * cols)
        throw initializer_wrong_size{};
    elements = new double[rows * cols];
    for (size_t i{0}; i < input_elements.size(); i++)
        elements[i] = input_elements[i];
}

matrix::matrix(const matrix &m)
    : rows(m.rows), cols(m.cols)
{
    elements = new double[rows * cols];
    for (size_t i{0}; i < rows * cols; i++)
        elements[i] = m.elements[i];
}

matrix::matrix(matrix &&m)
    : rows(m.rows), cols(m.cols), elements(m.elements)
{
    m.rows = 0;
    m.cols = 0;
    m.elements = nullptr;
}

matrix &matrix::operator=(const matrix &m)
{
    rows = m.rows;
    cols = m.cols;
    delete[] elements;
    elements = new double[rows * cols];
    for (size_t i{0}; i < rows * cols; i++)
        elements[i] = m.elements[i];
    return *this;
}

matrix &matrix::operator=(matrix &&m)
{
    rows = m.rows;
    cols = m.cols;
    delete[] elements;
    elements = m.elements;
    m.rows = 0;
    m.cols = 0;
    m.elements = nullptr;
    return *this;
}

size_t matrix::get_rows() const
{
    return rows;
}

size_t matrix::get_cols() const
{
    return cols;
}

double &matrix::operator()(const size_t &row, const size_t &col)
{
    if (row >= rows or col >= cols)
        throw out_of_bounds{};
    return elements[(cols * row) + col];
}

double matrix::operator()(const size_t &row, const size_t &col) const
{
    if (row >= rows or col >= cols)
        throw out_of_bounds{};
    return elements[(cols * row) + col];
}

matrix::~matrix()
{
    delete[] elements;
}

ostream &operator<<(ostream &out, const matrix &m)
{
    for (size_t i{0}; i < m.get_rows(); i++)
    {
        cout << "( ";
        for (size_t j{0}; j < m.get_cols(); j++)
            cout << m(i, j) << '\t'; // \t = tab character for (minimal) formatting
        cout << ")\n";
    }
    cout << '\n';
    return out;
}

matrix operator+(const matrix &a, const matrix &b)
{
    size_t rows{a.get_rows()}, cols{a.get_cols()};
    if ((rows != b.get_rows()) or (cols != b.get_cols()))
        throw matrix::incompatible_sizes_add{};
    matrix c{rows, cols};
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            c(i, j) = a(i, j) + b(i, j);
    return c;
}

matrix operator+=(matrix &a, const matrix &b)
{
    a = a + b;
    return a;
}

matrix operator-(const matrix &m)
{
    size_t rows{m.get_rows()}, cols{m.get_cols()};
    matrix c{rows, cols};
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            c(i, j) = -m(i, j);
    return c;
}

matrix operator-(const matrix &a, const matrix &b)
{
    return a + (-b);
}

matrix operator-=(matrix &a, const matrix &b)
{
    a = a - b;
    return a;
}

matrix operator*(const matrix &a, const matrix &b)
{
    size_t a_rows{a.get_rows()}, a_cols{a.get_cols()};
    size_t b_rows{b.get_rows()}, b_cols{b.get_cols()};
    if (a_cols != b_rows)
        throw matrix::incompatible_sizes_multiply{};
    matrix c{a_rows, b_cols};
    for (size_t i{0}; i < a_rows; i++)
        for (size_t j{0}; j < b_cols; j++)
            for (size_t k{0}; k < a_cols; k++)
                c(i, j) += a(i, k) * b(k, j);
    return c;
}

matrix operator*(const double &s, const matrix &m)
{
    size_t rows{m.get_rows()}, cols{m.get_cols()};
    matrix c{rows, cols};
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            c(i, j) = s * m(i, j);
    return c;
}

matrix operator*(const matrix &m, const double &s)
{
    return s * m;
}