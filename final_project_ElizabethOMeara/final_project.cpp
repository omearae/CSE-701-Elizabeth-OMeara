#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cmath>
#include "final_project.hpp"

//g++ final_project.cpp -Wall -Wextra -Wpedantic use to check for errors
using namespace std;

int main()
{
    clock_t tStart = clock();
    /* First we check to make sure the fitting mechanism works by fitting to simulated data where we know the parameters */
    try
    {
        /* Here I use the class read_report to retrieve parameters from a .txt file. These are then used to simulate an epidemic
        using the class solve_SIR with the given parameters. */
        read_report parameter_test("params.txt");
        vector<double> params_test;
        params_test = parameter_test.getData();

        solve_SIR test_solve(params_test[0], params_test[1], params_test[2], params_test[3], params_test[4]);
        vector<double> reports_test{test_solve.getSolve()};

        /* With this data we attempt to fit an SIR curve and output the fitted parameters */
        fit_param test_fit(reports_test, params_test[0], params_test[4]);
        vector<double> fitted_params_test{test_fit.getParam()};

        cout << "The initial parameters are: R_0 = " << params_test[2] << " and gamma = " << params_test[3] << endl;
        cout << "The fitted parameters are: R_0 = " << fitted_params_test[0] << " and gamma = " << fitted_params_test[1] << endl;
    }
    catch (const solve_SIR::param_non_positive &e)
    {
        cout << "Error: Parameter inputs have one or more negative values." << endl;
        return -1;
    }
    catch (const solve_SIR::no_epidemic &e)
    {
        cout << "Error: R0 input will result in no epidemic." << endl;
        return -1;
    }
    catch (const solve_SIR::not_in_R0_range &e)
    {
        cout << "Error: R0 input is not in the range of R0 used in the fitting mechanism." << endl;
        return -1;
    }
    catch (const solve_SIR::not_in_gamma_range &e)
    {
        cout << "Error: gamma input is not in the range of gamma values used in the fitting mechanism." << endl;
        return -1;
    }

    /* Now that we know the fitting mechanism works, we can fit the model to real data in order 
    to estimate R0 and gamma for the epidemic wave */

    read_report read_data("data.txt");
    vector<double> real_reports{read_data.getData()};

    /* Since we need to know how long we want to run the simulations for ie. same length as the given data, 
    we need to define Timelength to be the size of real_reports */
    int Timelength;

    for (size_t i = 0; i < real_reports.size(); i++)
    {
        if (real_reports[i] == real_reports.back())
        {
            Timelength = i + 1;
            break;
        }
    }

    /* Here we are getting the given population size for the epidemic from another file */
    read_population pop("population.txt");
    double pop_size{pop.getData()};

    /* Now that we have all the required data, we call fit_param to fit a model to the given data */
    fit_param epidemic_fit(real_reports, pop_size, Timelength);
    vector<double> fitted_epidemic_params{epidemic_fit.getParam()};

    cout << "The fitted parameters for the given epidemic wave are R0 = " << fitted_epidemic_params[0] << " and gamma = " << fitted_epidemic_params[1] << endl;
    cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}