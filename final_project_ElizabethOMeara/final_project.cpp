#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "final_project.hpp"

//g++ final_project.cpp -Wall -Wextra -Wpedantic use to check for errors
using namespace std;

int main()
{

    read_report reports("data.txt");

    vector<double> dataList{reports.getData()};

    read_population pop("population.txt");

    return 0;
}