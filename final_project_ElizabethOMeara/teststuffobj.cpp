#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <ctime>
#include "teststuffobj.hpp"

using namespace std;

int main()
{
    clock_t tStart = clock();
    double pop{1700000}, Iinit{1.0}, R0{2.4}, gamma_given{0.25};
    int totalt{122};

    try
    {
        solve_SIR test_solve(pop, Iinit, R0, gamma_given, totalt);
        vector<double> known_param_data(test_solve.getSolve());
        fit_param test_fit(known_param_data, pop, totalt);
        vector<double> test_fitted_params(test_fit.getParam());

        cout << "The initial parameters are: R_0 = " << R0 << " and gamma = " << gamma_given << endl;
        cout << "The fitted parameters are: R_0 = " << test_fitted_params[0] << " and gamma = " << test_fitted_params[1] << endl;
    }
    catch (const solve_SIR::param_non_positive &e)
    {
        cout << "Error: Parameter inputs have one or more negative values." << endl;
    }
    catch (const solve_SIR::no_epidemic &e)
    {
        cout << "Error: R0 input will result in no epidemic." << endl;
    }
    catch (const solve_SIR::not_in_R0_range &e)
    {
        cout << "Error: R0 input is not in the range of R0 used in the fitting mechanism." << endl;
    }
    catch (const solve_SIR::not_in_gamma_range &e)
    {
        cout << "Error: gamma input is not in the range of gamma values used in the fitting mechanism." << endl;
    }

    cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}