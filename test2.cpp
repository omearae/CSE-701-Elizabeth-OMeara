#include <random>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double N{50000};
    const int M{50000};
    double gillespie_results[M][4];
    double t_0{0};
    double I_0{20};
    double R_0{0};
    double S_0{N - I_0 - R_0};
    double mu{0.02 / 365};
    double beta{1};
    double gamma{0.25};
    gillespie_results[0][0] = t_0;
    gillespie_results[0][1] = S_0;
    gillespie_results[0][2] = I_0;
    gillespie_results[0][3] = R_0;
    for (size_t i = 0; i < M - 1; i++)
    {
        double S = gillespie_results[i, 1];
        double I = gillespie_results[i, 2];
        double R = gillespie_results[i, 3];
        double a_1{S * mu};
        double a_2{beta * S * I / N};
        double a_3{gamma * I};
        double a_4{mu * S};
        double a_5{mu * I};
        double a_6{mu * R};
        double a_0{a_1 + a_2 + a_3 + a_4 + a_5 + a_6};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double u{dis(gen)};
        double t{gillespie_results(i, 0)};
        double dt{(1 / a_0) * log(1 / (1 - u))};
        double tnew{t + dt};
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_real_distribution<> dis1(0.0, a_0);
        double v{dis1(gen1)};
        if (0 <= v && v < a_1)
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_1[0];
            gillespie_results[i + 1, 2] = E_1[1];
            gillespie_results[i + 1, 3] = E_1[2];
        }
        else if (a_1 <= v && v < a_1 + a_2)
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_2[0];
            gillespie_results[i + 1, 2] = E_2[1];
            gillespie_results[i + 1, 3] = E_2[2];
        }
        else if (a_1 + a_2 <= v && v < a_1 + a_2 + a_3)
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_3[0];
            gillespie_results[i + 1, 2] = E_3[1];
            gillespie_results[i + 1, 3] = E_3[2];
        }
        else if (a_1 + a_2 + a_3 <= v && v < a_1 + a_2 + a_3 + a_4)
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_4[0];
            gillespie_results[i + 1, 2] = E_4[1];
            gillespie_results[i + 1, 3] = E_4[2];
        }
        else if (a_1 + a_2 + a_3 + a_4 <= v && v < a_1 + a_2 + a_3 + a_4 + a_5)
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_5[0];
            gillespie_results[i + 1, 2] = E_5[1];
            gillespie_results[i + 1, 3] = E_5[2];
        }
        else
        {
            gillespie_results[i + 1, 0] = tnew;
            gillespie_results[i + 1, 1] = E_6[0];
            gillespie_results[i + 1, 2] = E_6[1];
            gillespie_results[i + 1, 3] = E_6[2];
        }
    }
}