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

int main()
{
    double N{1700000}, I0{1}, reproductionnumber{2.4}, gamma{0.25};
    int totaltime{122};
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

    vector<double> reproduction_estimates(500), gamma_estimates(450);
    double step_size_reproduction{0.01}, reproduction_start{1}, step_size_gamma{0.001}, gamma_start{0.05};

    reproduction_estimates[0] = reproduction_start;
    gamma_estimates[0] = gamma_start;

    for (int i = 0; i < 500 - 1; i++)
    {
        reproduction_estimates[i + 1] = reproduction_estimates[i] + step_size_reproduction;
    }

    for (int j = 0; j < 450 - 1; j++)
    {
        gamma_estimates[j + 1] = gamma_estimates[j] + step_size_gamma;
    }

    vector<vector<double>> LS_statistic(500, vector<double>(450));
    double I_init{1};
    vector<double> difference(totaltime + 1), difference_squared(totaltime + 1);

    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 450; j++)
        {
            double N1{1700000}, I01{1}, reproductionnumber1{reproduction_estimates[i]}, gamma1{gamma_estimates[j]};
            int totaltime1{122};
            vector<double> Snew1(totaltime), Inew1(totaltime), Rnew1(totaltime);
            Snew1[0] = N1 - I01;
            Inew1[0] = I01;
            Rnew1[0] = 0;
            vector<double> k11(2), k21(2), k31(2), k41(2);
            for (int i = 0; i < totaltime1 - 1; i++)
            {
                k11[0] = -reproductionnumber1 * gamma1 * Snew1[i] * Inew1[i] / N1;
                k11[1] = (reproductionnumber1 * gamma1 * Snew1[i] * Inew1[i] / N1) - gamma1 * Inew1[i];

                k21[0] = (-reproductionnumber1 * gamma1 / N) * (Snew1[i] + k11[0] / 2) * (Inew1[i] + k11[1] / 2);
                k21[1] = ((reproductionnumber1 * gamma1 / N) * (Snew1[i] + k11[0] / 2) * (Inew1[i] + k11[1] / 2)) - gamma1 * (Inew1[i] + k11[1] / 2);

                k31[0] = (-reproductionnumber1 * gamma1 / N) * (Snew1[i] + k21[0] / 2) * (Inew1[i] + k21[1] / 2);
                k31[1] = ((reproductionnumber1 * gamma1 / N) * (Snew1[i] + k21[0] / 2) * (Inew1[i] + k21[1] / 2)) - gamma1 * (Inew1[i] + k21[1] / 2);

                k41[0] = (-reproductionnumber1 * gamma1 / N) * (Snew1[i] + k31[0]) * (Inew1[i] + k31[1]);
                k41[1] = ((reproductionnumber1 * gamma1 / N) * (Snew1[i] + k31[0]) * (Inew1[i] + k31[1])) - gamma1 * (Inew1[i] + k31[1]);

                Snew1[i + 1] = Snew1[i] + ((k11[0] + 2 * k21[0] + 2 * k31[0] + k41[0]) / 6);
                Inew1[i + 1] = Inew1[i] + ((k11[1] + 2 * k21[1] + 2 * k31[1] + k41[1]) / 6);
                Rnew1[i + 1] = N1 - Snew1[i + 1] - Inew1[i + 1];
            }

            try
            {
                difference = Inew - Inew1;
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
    vector<double> min_each_column(500);
    double min_LS;

    for (int m = 0; m < 500; m++)
    {
        min_each_column[m] = my_min(LS_statistic[m]);
    }

    min_LS = my_min(min_each_column);

    int min_r_location, min_gamma_location;

    for (int h = 0; h < 500 - 1; h++)
    {
        for (int l = 0; l < 450 - 1; l++)
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

    cout << fitted_params << endl;
}