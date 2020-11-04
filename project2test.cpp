#include <iostream>
#include <cmath>
#include <vector>
#include <random>
using namespace std;
int main()
{
    int i;
    const double N{50000};
    const int M{50000};
    vector<double> susceptible[M];
    vector<double> infectious[M];
    vector<double> recovered[M];
    vector<double> event_time[M];
    double t_0{0};
    double I_0{20};
    double R_0{0};
    double S_0{N - I_0 - R_0};
    double mu{0.02 / 365};
    double beta{1};
    double gamma{0.25};
    susceptible.assign(1, S_0);
    infectious.assign(1, I_0);
    recovered.assign(1, R_0);
    event_time.assign(1, t_0);
    for (i = 0; i < M - 1; i++)
    {
        double S{susceptible[i]};
        double I{infectious[i]};
        double R{recovered[i]};
        double a_1{S * mu};
        double a_2{beta * S * I / N};
        double a_3{gamma * I};
        double a_4{mu * S};
        double a_5{mu * I};
        double a_6{mu * R};
        double a_0{a_1 + a_2 + a_3 + a_4 + a_5 + a_6};
        vector<double> E_1{S + 1, I, R};
        vector<double> E_2{S - 1, I + 1, R};
        vector<double> E_3{S, I - 1, R + 1};
        vector<double> E_4{S - 1, I, R};
        vector<double> E_5{S, I - 1, R};
        vector<double> E_6{S, I, R - 1};
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        double u{dis(gen)};
        double t{event_time[i]};
        double dt{(1 / a_0) * log(1 / (1 - u))};
        double tnew{t + dt};
        random_device rd1;
        mt19937 gen1(rd1());
        uniform_real_distribution<> dis1(0.0, a_0);
        double v{dis1(gen1)};
        if (0 <= v && v < a_1)
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_1[0];
            infectious[i + 1] = E_1[1];
            recovered[i + 1] = E_1[2];
        }
        else if (a_1 <= v && v < a_1 + a_2)
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_2[0];
            infectious[i + 1] = E_2[1];
            recovered[i + 1] = E_2[2];
        }
        else if (a_1 + a_2 <= v && v < a_1 + a_2 + a_3)
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_3[0];
            infectious[i + 1] = E_3[1];
            recovered[i + 1] = E_3[2];
        }
        else if (a_1 + a_2 + a_3 <= v && v < a_1 + a_2 + a_3 + a_4)
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_4[0];
            infectious[i + 1] = E_4[1];
            recovered[i + 1] = E_4[2];
        }
        else if (a_1 + a_2 + a_3 + a_4 <= v && v < a_1 + a_2 + a_3 + a_4 + a_5)
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_5[0];
            infectious[i + 1] = E_5[1];
            recovered[i + 1] = E_5[2];
        }
        else
        {
            event_time[i + 1] = tnew;
            susceptible[i + 1] = E_6[0];
            infectious[i + 1] = E_6[1];
            recovered[i + 1] = E_6[2];
        }
    }
}