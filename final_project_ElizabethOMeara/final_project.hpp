#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

class size_must_match
{
};

ostream &operator<<(ostream &out, const vector<double> &v)
{
    size_t s{v.size() - 1};
    out << "(";
    for (size_t i{0}; i < s; i++)
        out << v[i] << ", ";
    out << v[s] << ")\n";
    return out;
}

vector<double> operator-(const vector<double> &vec1, const vector<double> &vec2)
{
    size_t s{vec1.size()};
    vector<double> vec3(s, 0);
    if (s != vec2.size())
    {
        throw size_must_match{};
    }
    for (size_t i{0}; i < s; i++)
    {
        vec3[i] = abs(vec1[i] - vec2[i]);
    }
    return vec3;
}

/* Overloading the * operator for two vector<double> to evaluate the element-wise multiplication instead of dot product */
vector<double> operator*(const vector<double> &vec1, const vector<double> &vec2)
{
    size_t s{vec1.size()};
    vector<double> vec3(s, 0);
    if (s != vec2.size())
    {
        throw size_must_match{};
    }
    for (size_t i{0}; i < s; i++)
    {
        vec3[i] = vec1[i] * vec2[i];
    }
    return vec3;
}

/* Writing my own sum function as the usual one does not add in the final element */
double sum(vector<double> vec)
{
    size_t s{vec.size()};
    double sum_of_vector;
    double sum_init{vec[0]};
    for (size_t i = 0; i < s - 1; i++)
    {
        sum_of_vector = sum_init + vec[i + 1];
        sum_init = sum_of_vector;
    }
    return sum_of_vector;
}

/* Writing my own minimum function as the usual one was not working for me */
double my_min(vector<double> vec)
{
    size_t s{vec.size()};
    double min;
    double min_temp{vec[0]};
    for (size_t i = 0; i < s - 1; i++)
    {
        if (min_temp < vec[i + 1])
        {
            min_temp = min_temp;
        }
        else
        {
            min_temp = vec[i + 1];
        }
        min = min_temp;
    }
    return min;
}

/* Creating classes and a member functions to read a file containing data and return a vector or value */
class read_report
{
    string fileName;

public:
    read_report(string filename) : fileName(filename)

    {
    }

    vector<double> getData();
};

vector<double> read_report::getData()
{
    ifstream file(fileName);
    vector<double> dataList;
    double test;

    while (file >> test)
    {
        dataList.push_back(test);
    }
    file.close();

    return dataList;
}

class read_population
{

public:
    read_population(string filenamePop) : fileNamePop(filenamePop)

    {
    }
    double getData();

private:
    string fileNamePop;
};

double read_population::getData()
{
    ifstream filePop;

    filePop.open(fileNamePop);

    double valuePop;
    filePop >> valuePop;
    filePop.close();
    return valuePop;
}

/* Creating a class and member function that solves the SIR model using the RK4 method given parameter inputs */
class solve_SIR
{
public:
    solve_SIR(double input_N, double &input_I0, double &input_reproductionnumber, double &input_gamma, int input_totaltime)
        : N{input_N}, I0{input_I0}, reproductionnumber{input_reproductionnumber}, gamma{input_gamma}, totaltime{input_totaltime}
    {
    }
    vector<double> getSolve();

    class param_non_positive
    {
    };

    class no_epidemic
    {
    };

    class not_in_R0_range
    {
    };

    class not_in_gamma_range
    {
    };

private:
    double N, I0, reproductionnumber, gamma;
    int totaltime;
};

vector<double> solve_SIR::getSolve()
{
    if (N <= 0)
    {
        throw param_non_positive{};
    }

    if (I0 <= 0)
    {
        throw param_non_positive{};
    }

    if (reproductionnumber <= 1)
    {
        throw no_epidemic{};
    }

    if (reproductionnumber > 6.5)
    {
        throw not_in_R0_range{};
    }

    if (gamma <= 0)
    {
        throw param_non_positive{};
    }

    if (gamma < 0.05)
    {
        throw not_in_gamma_range{};
    }

    if (gamma > 1)
    {
        throw not_in_gamma_range{};
    }

    vector<double> Snew(totaltime), Inew(totaltime), Rnew(totaltime);
    Snew[0] = N - I0;
    Inew[0] = I0;
    Rnew[0] = 0;
    vector<double> k1(2), k2(2), k3(2), k4(2);
    for (int i = 0; i < totaltime - 1; i++)
    {
        k1[0] = -reproductionnumber * gamma * Snew[i] * Inew[i] / N;
        k1[1] = (reproductionnumber * gamma * Snew[i] * Inew[i] / N) - gamma * Inew[i];

        k2[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k1[0] / 2) * (Inew[i] + k1[1] / 2);
        k2[1] = ((reproductionnumber * gamma / N) * (Snew[i] + k1[0] / 2) * (Inew[i] + k1[1] / 2)) - gamma * (Inew[i] + k1[1] / 2);

        k3[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k2[0] / 2) * (Inew[i] + k2[1] / 2);
        k3[1] = ((reproductionnumber * gamma / N) * (Snew[i] + k2[0] / 2) * (Inew[i] + k2[1] / 2)) - gamma * (Inew[i] + k2[1] / 2);

        k4[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k3[0]) * (Inew[i] + k3[1]);
        k4[1] = ((reproductionnumber * gamma / N) * (Snew[i] + k3[0]) * (Inew[i] + k3[1])) - gamma * (Inew[i] + k3[1]);

        Snew[i + 1] = Snew[i] + ((k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]) / 6);
        Inew[i + 1] = Inew[i] + ((k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6);
        Rnew[i + 1] = N - Snew[i + 1] - Inew[i + 1];
    }
    return Inew;
}

/* Creating a class and member function that search through 550 x 900 (R0, gamma) 
pairs in order to find the best fit by finding the minimum least squares statistic of all simulations. */
class fit_param
{
public:
    fit_param(vector<double> &input_reports, double input_popsize, int input_reportlength)
        : reports{input_reports}, popsize{input_popsize}, report_length{input_reportlength}
    {
    }
    vector<double> getParam();

private:
    vector<double> reports;
    double popsize;
    int report_length;
};

vector<double> fit_param::getParam()
{
    /* Here the range of R0s and gammas that the program should search through to find the best fit is created */
    vector<double> reproduction_estimates(550), gamma_estimates(900);
    double step_size_reproduction{0.01}, reproduction_start{1}, step_size_gamma{0.001}, gamma_start{0.05};

    reproduction_estimates[0] = reproduction_start;
    gamma_estimates[0] = gamma_start;

    for (int i = 0; i < 550 - 1; i++)
    {
        reproduction_estimates[i + 1] = reproduction_estimates[i] + step_size_reproduction;
    }

    for (int j = 0; j < 900 - 1; j++)
    {
        gamma_estimates[j + 1] = gamma_estimates[j] + step_size_gamma;
    }

    /* With the parameter ranges, the SIR model is solved for each pair and then the Least Squares Statistic 
    between the result and the real data is calculated for each pair. */
    vector<vector<double>> LS_statistic(550, vector<double>(900));
    double I_init{1};
    vector<double> difference(report_length), difference_squared(report_length);

    for (int i = 0; i < 550; i++)
    {
        for (int j = 0; j < 900; j++)
        {
            solve_SIR solve(popsize, I_init, reproduction_estimates[i], gamma_estimates[j], report_length);
            vector<double> reports_estimated(solve.getSolve());

            try
            {
                difference = reports - reports_estimated;
            }
            catch (const size_must_match &e)
            {
                cout << "Error: Vector sizes don't match!\n";
            }

            try
            {
                difference_squared = difference * difference;
            }
            catch (const size_must_match &e)
            {
                cout << "Error: Vector sizes don't match!\n";
            }
            (LS_statistic[i])[j] = sum(difference_squared);
        }
    }

    /* Once the least squares statistics are estimated, the minimum is found below.  */
    vector<double> min_each_column(550);
    double min_LS;

    for (int m = 0; m < 550; m++)
    {
        min_each_column[m] = my_min(LS_statistic[m]);
    }

    min_LS = my_min(min_each_column);

    int min_r_location, min_gamma_location;

    /* Now the location at which the minimum exists is found in order to determine the best fit parameters */
    for (int h = 0; h < 550 - 1; h++)
    {
        for (int l = 0; l < 900 - 1; l++)
        {
            if ((LS_statistic[h])[l] == min_LS)
            {
                min_r_location = h;
                min_gamma_location = l;
                break;
            }
        }
    }

    vector<double> fitted_params(2);
    fitted_params[0] = reproduction_estimates[min_r_location];
    fitted_params[1] = gamma_estimates[min_gamma_location];

    return fitted_params;
}