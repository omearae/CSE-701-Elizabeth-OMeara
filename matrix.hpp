#include <iostream>
#include <vector>

using namespace std;

class matrix
{
public:
    // Constructor to create a zero matrix
    // First argument: size_t, number of rows
    // Second argument: size_t, number of columns
    matrix(const size_t &, const size_t &);

    // Constructor to create a diagonal matrix
    // First argument: vector<double>, the elements on the diagonal
    // Number of rows and columns is inferred automatically
    matrix(const vector<double> &);

    // Constructor to create a matrix and initialize it to the given elements
    // First argument: size_t, number of rows
    // Second argument: size_t, number of columns
    // Third argument: vector<double>, the elements (flattened)
    matrix(const size_t &, const size_t &, const vector<double> &);

    // Copy constructor to create a new matrix with the same elements as an existing matrix
    matrix(const matrix &);

    // Move constructor to move the elements of an existing matrix to a new matrix
    matrix(matrix &&);

    // Overloaded operator = to assign the elements of one matrix to another matrix
    matrix &operator=(const matrix &);

    // Overloaded operator = to move the elements of one matrix to another matrix
    matrix &operator=(matrix &&);

    // Member function used to obtain (but not modify) the number of rows in the matrix
    size_t get_rows() const;

    // Member function used to obtain (but not modify) the number of columns in the matrix
    size_t get_cols() const;

    // Overloaded operator () used to access matrix elements
    // The indices start from 0: m(0, 1) would be the element at row 1, column 2
    // First version: returns a reference, thus allows modification of the element
    double &operator()(const size_t &, const size_t &);

    // Overloaded operator () used to access matrix elements
    // The indices start from 0: m(0, 1) would be the element at row 1, column 2
    // Second version: does not return a reference and declared as const, does not allow modification of the element
    double operator()(const size_t &, const size_t &) const;

    // Exception to be thrown if the number of rows or columns given to the constructor is zero
    class zero_size
    {
    };

    // Exception to be thrown if the vector of elements provided to the constructor
    // does not match the desired number of rows and columns
    class initializer_wrong_size
    {
    };

    // Exception to be thrown if the requested index is out of bounds
    class out_of_bounds
    {
    };

    // Exception to be thrown if two matrices of different sizes are added or subtracted
    class incompatible_sizes_add
    {
    };

    // Exception to be thrown if two matrices of incompatible sizes are multiplied
    class incompatible_sizes_multiply
    {
    };

    // Destructor to free up the allocated memory
    ~matrix();

private:
    // The number of rows and columns
    size_t rows{0}, cols{0};

    // A vector storing the elements of the matrix in flattened (1-dimensional) form
    double *elements{nullptr};
};

// Overloaded binary operator << used to easily print out a matrix to a stream
ostream &operator<<(ostream &, const matrix &);

// Overloaded binary operator + used to add two matrices
matrix operator+(const matrix &, const matrix &);

// Overloaded binary operator += used to add two matrices and assign the result to the first one
matrix operator+=(matrix &, const matrix &);

// Overloaded unary operator - used to take the negative of a matrix
matrix operator-(const matrix &);

// Overloaded binary operator - used to subtract two matrices
matrix operator-(const matrix &, const matrix &);

// Overloaded binary operator -= used to subtract two matrices and assign the result to the first one
matrix operator-=(matrix &, const matrix &);

// Overloaded binary operator * used to multiply two matrices
matrix operator*(const matrix &, const matrix &);

// Overloaded binary operator * used to multiply a scalar on the left and a matrix on the right
matrix operator*(const double &, const matrix &);

// Overloaded binary operator * used to multiply a matrix on the left and a scalar on the right
matrix operator*(const matrix &, const double &);