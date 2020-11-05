# **Project 2: Using C++ to Simulate Epidemics and Estimate the Corresponding Values of the growth rate r and the doubling time Td** \ Elizabeth O'Meara 400054293 \ November 8, 2020

## Summary

I created this program to simulate an epidemic and estimate the values of r and Td from the simulated data. The program uses the Gillespie Algorithm to simulate epidemic data using two models, the SIR model and the SEIR model. By inputting values for the population size, number of iterations, inital values of each compartment (S, E, I, R), gamma (where 1/gamma is the mean infectious period), sigma (where 1/sigma is the mean latent period), and birth/death rate, and the reproduction number R_0, the data is generated separately for the SIR and SEIR models. The growth rate r is then estimated as the slope of the initial growth phase of the ln of the incidence data. Thus, the least squares method was used to fit a line to the corresponding data, where its slope = r. Once r is estimated, Td is calculated using the doubling time formula. The output of this program is a table comparing estimates of r and Td for the SIR and SEIR models for different values of R_0.

## Implementation

### Operator Overloading for Vector Addition, Subtraction, Addition of a Scalar to a Vector, and Multiplication and Setting Namespace

First, so that we wouldn't have to specify the namespace `std` in each line of the code, we set the namespace with the following code.

` using namespace std; `\

Next, since this program will require specific methods of vector addition, subtraction, addition of a scalar to a vector and vector multiplication, the first step in the program is to define the different operator overloads. An example of this for the overload of * operator is as follows. Note that this is not the typical vector multiplication, but it is the type of multiplication required for a calculation in the program.

`vector<double> operator*(const vector<double> &v, const vector<double> &w)`\
`{`\
`size_t s{v.size()};`\
`vector<double> u(s, 0);`\
`if (s != w.size())`\
`throw size_must_match{};`\
`for (size_t i{0}; i < s; i++)`\
`u[i] += v[i] * w[i];`\
`return u;`\
`}`

### The Gillespie Algorithm
