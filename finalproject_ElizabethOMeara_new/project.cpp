#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <ctime>

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

class read_params
{
    string fileNameParams;

public:
    read_params(string filenameparams) : fileNameParams(filenameparams)

    {
    }

    vector<double> getDataParams();
};

vector<double> read_params::getDataParams()
{
    ifstream fileparams(fileNameParams);

    vector<double> test_params;
    double value2;

    while (fileparams >> value2)
    {
        test_params.push_back(value2);
    }
    fileparams.close();

    return test_params;
}

class read_population
{
    string fileNamePop;

public:
    read_population(string filenamePop) : fileNamePop(filenamePop)

    {
    }
    double getData();
};

double read_population::getData()
{
    ifstream filePop(fileNamePop);
    double valuePop;
    filePop >> valuePop;
    filePop.close();
    return valuePop;
}

//g++ project.cpp -Wall -Wextra -Wpedantic use to check for errors

int main()
{
    read_report read_epidemic("data.txt");
    vector<double> real_epidemic{read_epidemic.getData()};

    read_params parameter_test("params.txt");
    vector<double> params_test{parameter_test.getDataParams()};

    cout << real_epidemic[0] << endl;
}