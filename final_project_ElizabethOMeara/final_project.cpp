#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <ctime>
#include "final_project.hpp"

//g++ final_project.cpp -Wall -Wextra -Wpedantic use to check for errors
using namespace std;

int main()
{
    clock_t tStart = clock();
    read_report read_data("data.txt");
    vector<double> real_reports{read_data.getData()};

    /* read_population pop("population.txt"); */
    /* double N{pop.getData()}; */

    read_report parameter_test("params.txt");
    vector<double> params_test{parameter_test.getData()};

    solve_SIR test_solve(params_test[0], params_test[1], params_test[2], params_test[3], params_test[4]);

    vector<double> reports_test{test_solve.getSolve()};

    fit_param test_fit(reports_test, params_test[0], params_test[4]);
    vector<double> fitted_params_test{test_fit.getParam()};

    cout << "The initial parameters are: R_0 = " << params_test[2] << " and gamma = " << params_test[3] << endl;
    cout << "The fitted parameters are: R_0 = " << fitted_params_test[0] << " and gamma = " << fitted_params_test[1] << endl;

    cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}