#include <vector>

using namespace std;

class size_must_match
{
};

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