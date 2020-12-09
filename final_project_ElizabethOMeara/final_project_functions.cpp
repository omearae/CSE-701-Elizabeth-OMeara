#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "final_project_functions.hpp"

using namespace std;

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

vector<double> read_report::getData()
{
    ifstream file{fileName};
    if (!file)
    {
        perror("Error opening input file");
    }

    vector<double> dataList;
    double test;

    while (file >> test)
    {
        dataList.push_back(test);
    }
    file.close();

    return dataList;
}

double read_population::getData()
{
    ifstream filePop;

    filePop.open(fileNamePop);

    double valuePop;
    filePop >> valuePop;
    filePop.close();
    return valuePop;
}

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

vector<double> fit_param::getParam()
{
    /* Here the range of R0s and gammas that the program should search through to find the best fit is created */
    vector<double> reproduction_estimates(550), gamma_estimates(900);
    double step_size_reproduction{0.01}, reproduction_start{1.01}, step_size_gamma{0.001}, gamma_start{0.05};

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
    vector<double> difference(report_length), difference_squared(report_length), reports_estimated(report_length);

    for (int i = 0; i < 550; i++)
    {
        for (int j = 0; j < 900; j++)
        {
            solve_SIR solve(popsize, I_init, reproduction_estimates[i], gamma_estimates[j], report_length);

            reports_estimated = solve.getSolve();

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
        min_each_column[m] = *min_element(LS_statistic[m].begin(), LS_statistic[m].end());
    }

    min_LS = *min_element(min_each_column.begin(), min_each_column.end());

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
