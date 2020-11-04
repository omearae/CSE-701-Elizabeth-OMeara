#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;
class size_must_match
{
};
ostream &operator<<(ostream &out, const vector<double> &v)
{
    size_t s{v.size() - 1};
    out << "(";
    for (size_t i{0}; i < s; i++)
        out << v[i] << ", ";
    out << v[s] << ")\n";
    return out;
}
vector<double> operator*(const vector<double> &v, const vector<double> &w)
{
    size_t s{v.size()};
    vector<double> u(s, 0);
    if (s != w.size())
        throw size_must_match{};
    for (size_t i{0}; i < s; i++)
        u[i] += v[i] * w[i];
    return u;
}
vector<double> operator+(const vector<double> &v, const vector<double> &w)
{
    size_t s{v.size()};
    vector<double> u(s, 0);
    if (s != w.size())
        throw size_must_match{};
    for (size_t i{0}; i < s; i++)
        u[i] = v[i] + w[i];
    return u;
}
vector<double> operator-(const vector<double> &v, const vector<double> &w)
{
    size_t s{v.size()};
    vector<double> u(s, 0);
    if (s != w.size())
        throw size_must_match{};
    for (size_t i{0}; i < s; i++)
        u[i] = v[i] - w[i];
    return u;
}
vector<double> operator-(const vector<double> &v, const double &w)
{
    size_t s{v.size()};
    vector<double> u(s, 0);
    for (size_t i{0}; i < s; i++)
        u[i] = v[i] - w;
    return u;
}

int main()
{
    clock_t tStart = clock();
    int i;
    const double N{5000000};
    const int M{500000};
    vector<double> susceptible(M);
    vector<double> infectious(M);
    vector<double> recovered(M);
    vector<double> event_time(M);
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
    vector<double> log_incidence(M);
    for (i = 0; i < M - 1; i++)
    {
        log_incidence[i] = log(infectious[i]);
    }
    double max_log_incidence = *max_element(log_incidence.begin(), log_incidence.end());
    int max_location;
    for (i = 0; i < M - 1; i++)
    {
        if (log_incidence[i] == max_log_incidence)
        {
            max_location = i;
            break;
        }
    }
    double min_log_incidence = *min_element(log_incidence.begin(), log_incidence.end());
    int min_location;
    for (i = 0; i < M - 1; i++)
    {
        if (log_incidence[i] == min_log_incidence)
        {
            min_location = i;
            break;
        }
    }
    vector<double> least_square_data_incidence(max_location);
    for (i = 0; i < max_location - 1; i++)
    {
        least_square_data_incidence[i] = log_incidence[i];
    }
    vector<double> least_square_data_event_time(max_location);
    for (i = 0; i < max_location - 1; i++)
    {
        least_square_data_event_time[i] = event_time[i];
    }
    double sum_least_square_data_incidence{accumulate(least_square_data_incidence.begin(), least_square_data_incidence.end(), 0)};
    double sum_least_square_data_event_time{accumulate(least_square_data_event_time.begin(), least_square_data_event_time.end(), 0)};
    double mean_least_square_data_incidence{sum_least_square_data_incidence / max_location};
    double mean_least_square_data_event_time{sum_least_square_data_event_time / max_location};

    vector<double> dist_mean_incidence(max_location);
    vector<double> dist_mean_event_time(max_location);
    vector<double> dist_mean_event_time_squared(max_location);
    vector<double> multiply_dist_incidence_event_time(max_location);

    dist_mean_incidence = least_square_data_incidence - mean_least_square_data_incidence;
    dist_mean_event_time = least_square_data_event_time - mean_least_square_data_event_time;
    dist_mean_event_time_squared = dist_mean_event_time * dist_mean_event_time;
    multiply_dist_incidence_event_time = dist_mean_event_time * dist_mean_incidence;

    double sum_multiply_dist_incidence_event_time{accumulate(multiply_dist_incidence_event_time.begin(), multiply_dist_incidence_event_time.end(), 0)};
    double sum_dist_mean_event_time_squared{accumulate(dist_mean_event_time_squared.begin(), dist_mean_event_time_squared.end(), 0)};
    double r_growth_rate{sum_multiply_dist_incidence_event_time / sum_dist_mean_event_time_squared};

    cout << "The growth rate of this simulated epidemic is " << r_growth_rate << endl;
    cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}