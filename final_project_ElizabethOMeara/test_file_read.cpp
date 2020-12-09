#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <filesystem>

using namespace std;

int main()
{
    ifstream reports;
    reports.open("data.txt");

    if (!reports)
    {
        perror("Error opening input file");
        return -1;
    }

    vector<double> dataList;
    double test;

    while (reports >> test)
    {
        dataList.push_back(test);
    }
    reports.close();

    cout << dataList[0] << endl;
}