#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class read_report
{
    string fileName;

public:
    read_report(string filename) : fileName(filename)

    {
    }

    vector<int> getData();
};

vector<int> read_report::getData()
{
    ifstream file(fileName);

    vector<int> dataList;
    int value;

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
