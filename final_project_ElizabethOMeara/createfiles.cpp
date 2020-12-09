#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ofstream outfile{"paramstest.txt"};

    if (!outfile)
    {
        perror("Error opening output file");
        return -1;
    }

    outfile << 1700000 << std::endl;
    outfile << 1 << std::endl;
    outfile << 2.4 << std::endl;
    outfile << 0.25 << std::endl;
    outfile << 122 << std::endl;
    outfile.close();

    ifstream infile{"paramstest.txt"};

    if (!infile)
    {
        perror("Error opening input file");
        return -1;
    }

    vector<double> dataList;
    double test;

    while (infile >> test)
    {
        dataList.push_back(test);
    }
    infile.close();

    cout << dataList[0] << endl;
}