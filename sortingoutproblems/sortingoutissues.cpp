#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

class read_epidemic
{
public:
    read_epidemic(string epidemic_file) : Epidemic_File{epidemic_file}
    {
    }

    vector<double> getEpidemicData();

private:
    string Epidemic_File;
};

vector<double> read_epidemic::getEpidemicData()
{
    ifstream epidemicfile(Epidemic_File);

    vector<double> epidemiclist;
    double value;

    while (epidemicfile >> value)
    {
        epidemiclist.push_back(value);
    }
    epidemicfile.close();

    return epidemiclist;
}

int main()
{
    read_epidemic report_read("epidemicdata.txt");
    vector<double> report_data{report_read.getEpidemicData()};

    cout << report_data[0] << endl;
}