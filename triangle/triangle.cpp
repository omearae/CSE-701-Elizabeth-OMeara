#include <cmath>
#include <iostream>

#include "triangle.hpp"

using namespace std;

triangle::triangle(const double &input_a, const double &input_b, const double &input_c)
    : a{input_a}, b{input_b}, c{input_c}
{
    if ((a < 0) or (b < 0) or (c < 0))
    {
        cout << "Negative length encountered, taking absolute value. ";
        a = abs(a);
        b = abs(b);
        c = abs(c);
    }
    if ((a > b + c) or (b > c + a) or (c > a + b))
    {
        cout << "Triangle inequality not satisfied, taking default values instead. ";
        a = b = c = 0;
    }
    cout << "Initialized triangle with sides (" << a << ", " << b << ", " << c << ").\n";
}

triangle::triangle(const double &input)
{
    triangle(input, input, input);
}

triangle::triangle()
{
    triangle(0, 0, 0);
}