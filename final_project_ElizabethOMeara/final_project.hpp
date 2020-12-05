#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class size_must_match
{
};

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
        vec3[i] = vec1[i] - vec2[i];
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
    double value;

    while (file >> value)
    {
        dataList.push_back(value);
    }
    file.close();

    return dataList;
}

class read_population
{
    string fileNamePop;

public:
    read_population(string filenamePop) : fileNamePop(filenamePop)

    {
    }
    int getData();
};

int read_population::getData()
{
    ifstream filePop(fileNamePop);
    int valuePop;
    filePop >> valuePop;
    filePop.close();
    return valuePop;
}

class solve_SIR
{
public:
    solve_SIR(double &input_N, double &input_I0, long double &input_reproductionnumber, long double &input_gamma, int &input_totaltime)
        : N{input_N}, I0{input_I0}, reproductionnumber{input_reproductionnumber}, gamma{input_gamma}, totaltime{input_totaltime}
    {
    }
    vector<double> getSolve();

private:
    double N, I0;
    int totaltime;
    long double reproductionnumber, gamma;
};

vector<double> solve_SIR::getSolve()
{
    vector<double> Snew(totaltime + 1), Inew(totaltime + 1), Rnew(totaltime + 1);
    Snew[0] = N - I0;
    Inew[0] = I0;
    Rnew[0] = 0;
    vector<double> k1(2), k2(2), k3(2), k4(2);
    for (int i = 0; i < totaltime; i++)
    {
        k1[0] = -reproductionnumber * gamma * Snew[i] * Inew[i] / N;
        k1[1] = reproductionnumber * gamma * Snew[i] * Inew[i] / N - gamma * Inew[i];

        k2[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k1[0] / 2) * (Inew[i] + k1[1] / 2);
        k2[1] = (reproductionnumber * gamma / N) * (Snew[i] + k1[0] / 2) * (Inew[i] + k1[1] / 2) - gamma * (Inew[i] + k1[1] / 2);

        k3[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k2[0] / 2) * (Inew[i] + k2[1] / 2);
        k3[1] = (reproductionnumber * gamma / N) * (Snew[i] + k2[0] / 2) * (Inew[i] + k2[1] / 2) - gamma * (Inew[i] + k2[1] / 2);

        k4[0] = (-reproductionnumber * gamma / N) * (Snew[i] + k3[0]) * (Inew[i] + k3[1]);
        k4[1] = (reproductionnumber * gamma / N) * (Snew[i] + k3[0]) * (Inew[i] + k3[1]) - gamma * (Inew[i] + k3[1]);

        Snew[i + 1] = Snew[i] + (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]) / 6;
        Inew[i + 1] = Inew[i] + (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6;
        Rnew[i + 1] = N - Snew[i + 1] - Inew[i + 1];
    }
    return Inew;
}

class fit_param
{
public:
    fit_param(vector<double> &input_reports, double &input_popsize)
        : reports{input_reports}, popsize{input_popsize}
    {
    }
    vector<double> getParam();

private:
    vector<double> reports;
    double popsize;
};

vector<double> fit_param::getParam()
{
    vector<long double> reproduction_estimates(900), gamma_estimates(950);
    const long double step_size_reproduction{0.01}, reproduction_start{1}, reproduction_end{10}, step_size_gamma{0.001}, gamma_start{1}, gamma_end{1 / 20};

    reproduction_estimates[0] = reproduction_start;
    reproduction_estimates[899] = reproduction_end;
    gamma_estimates[0] = gamma_start;
    gamma_estimates[949] = gamma_end;

    for (int i = 0; i < reproduction_estimates.size() - 2; i++)
    {
        reproduction_estimates[i + 1] = reproduction_estimates[i] + step_size_reproduction;
    }

    for (int i = 0; i < gamma_estimates.size() - 2; i++)
    {
        gamma_estimates[i + 1] = gamma_estimates[i] - step_size_gamma;
    }

    vector<vector<long double>> LS_statistic(900, vector<long double>(950));
    double I_init{1};
    vector<double> difference(reports.size()), difference_squared(reports.size());

    for (int i = 0; i < reproduction_estimates.size() - 1; i++)
    {
        for (int j = 0; j < gamma_estimates.size() - 1; j++)
        {
            solve_SIR solve(popsize, I_init, reproduction_estimates[i], gamma_estimates[j], reports.size());
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
            LS_statistic[i][j] = accumulate(difference_squared.begin(), difference_squared.end(), 0);
        }
    }
    vector<long double> min_each_column(900);
    long double min_LS;

    for (int i = 0; i < reproduction_estimates.size() - 1; i++)
    {
        min_each_column[i] = *min_element(LS_statistic[i].begin(), LS_statistic[i].end());
    }

    min_LS{*min_element(min_each_column.begin(), min_each_column.end())};

    int min_reproduction_location, min_gamma_location;

    for (int i = 0; i < reproduction_estimates.size(); i++)
    {
        for (int j = 0; j < gamma_estimates.size(); j++)
        {
            if (LS_statistic[i][j] == min_LS)
            {
                min_reproduction_location{i};
                min_gamma_location{j};
                break;
            }
        }
    }

    vector<double> params{reproduction_estimates[min_reproduction_location], gamma_estimates[min_gamma_location]};

    return params;
}