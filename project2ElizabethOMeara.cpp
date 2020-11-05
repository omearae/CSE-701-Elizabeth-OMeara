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
    int j;
    vector<double> reproduction_number{2.7, 4, 12};
    cout << setw(30)
         << "SIR Model"
         << setw(30)
         << "SEIR Model"
         << endl;
    cout << "| "
         << setw(10)
         << "R_0"
         << " | "
         << setw(10)
         << "r"
         << " | "
         << setw(10)
         << "Td"
         << " | "
         << setw(10)
         << "R_0"
         << " | "
         << setw(10)
         << "r"
         << " | "
         << setw(10)
         << "Td"
         << " |" << endl;
    for (j = 0; j < 3; j++)
    {
        int i;
        const double N{5000000};
        const int M{500000};
        vector<double> susceptible_SIR(M);
        vector<double> infectious_SIR(M);
        vector<double> recovered_SIR(M);
        vector<double> event_time_SIR(M);
        vector<double> susceptible_SEIR(M);
        vector<double> exposed_SEIR(M);
        vector<double> infectious_SEIR(M);
        vector<double> recovered_SEIR(M);
        vector<double> event_time_SEIR(M);
        double t_0{0};
        double I_0{20};
        double R_0{0};
        double S_0_SIR{N - I_0 - R_0};
        double E_0_SEIR{0};
        double S_0_SEIR{N - I_0 - R_0 - E_0_SEIR};
        double mu{0.02 / 365};
        double gamma{0.25};
        double sigma{0.25};
        susceptible_SIR.assign(1, S_0_SIR);
        infectious_SIR.assign(1, I_0);
        recovered_SIR.assign(1, R_0);
        event_time_SIR.assign(1, t_0);
        susceptible_SEIR.assign(1, S_0_SEIR);
        exposed_SEIR.assign(1, E_0_SEIR);
        infectious_SEIR.assign(1, I_0);
        recovered_SEIR.assign(1, R_0);
        event_time_SEIR.assign(1, t_0);
        for (i = 0; i < M - 1; i++)
        {
            double S_SIR{susceptible_SIR[i]};
            double I_SIR{infectious_SIR[i]};
            double R_SIR{recovered_SIR[i]};

            double S_SEIR{susceptible_SEIR[i]};
            double E_SEIR{exposed_SEIR[i]};
            double I_SEIR{infectious_SEIR[i]};
            double R_SEIR{recovered_SEIR[i]};

            double a_1{N * mu};
            double a_2{reproduction_number[j] * (gamma + mu) * S_SIR * I_SIR / N};
            double a_3{gamma * I_SIR};
            double a_4{mu * S_SIR};
            double a_5{mu * I_SIR};
            double a_6{mu * R_SIR};

            double b_1{N * mu};
            double b_2{(reproduction_number[j] * (gamma + mu) * (sigma + mu) / sigma) * S_SEIR * I_SEIR / N};
            double b_3{sigma * E_SEIR};
            double b_4{gamma * I_SEIR};
            double b_5{mu * S_SEIR};
            double b_6{mu * E_SEIR};
            double b_7{mu * I_SEIR};
            double b_8{mu * R_SEIR};

            double a_0{a_1 + a_2 + a_3 + a_4 + a_5 + a_6};
            double b_0{b_1 + b_2 + b_3 + b_4 + b_5 + b_6 + b_7 + b_8};

            vector<double> E_1{S_SIR + 1, I_SIR, R_SIR};
            vector<double> E_2{S_SIR - 1, I_SIR + 1, R_SIR};
            vector<double> E_3{S_SIR, I_SIR - 1, R_SIR + 1};
            vector<double> E_4{S_SIR - 1, I_SIR, R_SIR};
            vector<double> E_5{S_SIR, I_SIR - 1, R_SIR};
            vector<double> E_6{S_SIR, I_SIR, R_SIR - 1};

            vector<double> E_1_SEIR{S_SEIR + 1, E_SEIR, I_SEIR, R_SEIR};
            vector<double> E_2_SEIR{S_SEIR - 1, E_SEIR + 1, I_SEIR, R_SEIR};
            vector<double> E_3_SEIR{S_SEIR, E_SEIR - 1, I_SEIR + 1, R_SEIR};
            vector<double> E_4_SEIR{S_SEIR, E_SEIR, I_SEIR - 1, R_SEIR + 1};
            vector<double> E_5_SEIR{S_SEIR - 1, E_SEIR, I_SEIR, R_SEIR};
            vector<double> E_6_SEIR{S_SEIR, E_SEIR - 1, I_SEIR, R_SEIR};
            vector<double> E_7_SEIR{S_SEIR, E_SEIR, I_SEIR - 1, R_SEIR};
            vector<double> E_8_SEIR{S_SEIR, E_SEIR, I_SEIR, R_SEIR - 1};

            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            double u{dis(gen)};
            double t{event_time_SIR[i]};
            double dt{(1 / a_0) * log(1 / (1 - u))};
            double tnew{t + dt};

            random_device rd1;
            mt19937 gen1(rd1());
            uniform_real_distribution<> dis1(0.0, a_0);
            double v{dis1(gen1)};

            if (0 <= v && v < a_1)
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_1[0];
                infectious_SIR[i + 1] = E_1[1];
                recovered_SIR[i + 1] = E_1[2];
            }
            else if (a_1 <= v && v < a_1 + a_2)
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_2[0];
                infectious_SIR[i + 1] = E_2[1];
                recovered_SIR[i + 1] = E_2[2];
            }
            else if (a_1 + a_2 <= v && v < a_1 + a_2 + a_3)
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_3[0];
                infectious_SIR[i + 1] = E_3[1];
                recovered_SIR[i + 1] = E_3[2];
            }
            else if (a_1 + a_2 + a_3 <= v && v < a_1 + a_2 + a_3 + a_4)
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_4[0];
                infectious_SIR[i + 1] = E_4[1];
                recovered_SIR[i + 1] = E_4[2];
            }
            else if (a_1 + a_2 + a_3 + a_4 <= v && v < a_1 + a_2 + a_3 + a_4 + a_5)
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_5[0];
                infectious_SIR[i + 1] = E_5[1];
                recovered_SIR[i + 1] = E_5[2];
            }
            else
            {
                event_time_SIR[i + 1] = tnew;
                susceptible_SIR[i + 1] = E_6[0];
                infectious_SIR[i + 1] = E_6[1];
                recovered_SIR[i + 1] = E_6[2];
            }
            random_device rd2;
            mt19937 gen2(rd2());
            uniform_real_distribution<> dis2(0.0, b_0);
            double v2{dis2(gen2)};

            if (0 <= v2 && v2 < b_1)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_1_SEIR[0];
                exposed_SEIR[i + 1] = E_1_SEIR[1];
                infectious_SEIR[i + 1] = E_1_SEIR[2];
                recovered_SEIR[i + 1] = E_1_SEIR[3];
            }
            else if (b_1 <= v2 && v2 < b_1 + b_2)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_2_SEIR[0];
                exposed_SEIR[i + 1] = E_2_SEIR[1];
                infectious_SEIR[i + 1] = E_2_SEIR[2];
                recovered_SEIR[i + 1] = E_2_SEIR[3];
            }
            else if (b_1 + b_2 <= v2 && v2 < b_1 + b_2 + b_3)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_3_SEIR[0];
                exposed_SEIR[i + 1] = E_3_SEIR[1];
                infectious_SEIR[i + 1] = E_3_SEIR[2];
                recovered_SEIR[i + 1] = E_3_SEIR[3];
            }
            else if (b_1 + b_2 + b_3 <= v2 && v2 < b_1 + b_2 + b_3 + b_4)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_4_SEIR[0];
                exposed_SEIR[i + 1] = E_4_SEIR[1];
                infectious_SEIR[i + 1] = E_4_SEIR[2];
                recovered_SEIR[i + 1] = E_4_SEIR[3];
            }
            else if (b_1 + b_2 + b_3 + b_4 <= v2 && v2 < b_1 + b_2 + b_3 + b_4 + b_5)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_5_SEIR[0];
                exposed_SEIR[i + 1] = E_5_SEIR[1];
                infectious_SEIR[i + 1] = E_5_SEIR[2];
                recovered_SEIR[i + 1] = E_5_SEIR[3];
            }
            else if (b_1 + b_2 + b_3 + b_4 + b_5 <= v2 && v2 < b_1 + b_2 + b_3 + b_4 + b_5 + b_6)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_6_SEIR[0];
                exposed_SEIR[i + 1] = E_6_SEIR[1];
                infectious_SEIR[i + 1] = E_6_SEIR[2];
                recovered_SEIR[i + 1] = E_6_SEIR[3];
            }
            else if (b_1 + b_2 + b_3 + b_4 + b_5 + b_6 <= v2 && v2 < b_1 + b_2 + b_3 + b_4 + b_5 + b_6 + b_7)
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_7_SEIR[0];
                exposed_SEIR[i + 1] = E_7_SEIR[1];
                infectious_SEIR[i + 1] = E_7_SEIR[2];
                recovered_SEIR[i + 1] = E_7_SEIR[3];
            }
            else
            {
                event_time_SEIR[i + 1] = tnew;
                susceptible_SEIR[i + 1] = E_8_SEIR[0];
                exposed_SEIR[i + 1] = E_8_SEIR[1];
                infectious_SEIR[i + 1] = E_8_SEIR[2];
                recovered_SEIR[i + 1] = E_8_SEIR[3];
            }
        }

        vector<double> log_incidence(M);
        vector<double> log_incidence_SEIR(M);

        for (i = 0; i < M - 1; i++)
        {
            log_incidence[i] = log(infectious_SIR[i]);
            log_incidence_SEIR[i] = log(infectious_SEIR[i]);
        }
        double max_log_incidence = *max_element(log_incidence.begin(), log_incidence.end());
        double max_log_incidence_SEIR = *max_element(log_incidence_SEIR.begin(), log_incidence_SEIR.end());

        int max_location;
        int max_location_SEIR;

        for (i = 0; i < M - 1; i++)
        {
            if (log_incidence[i] == max_log_incidence)
            {
                max_location = i;
                break;
            }
        }
        for (i = 0; i < M - 1; i++)
        {
            if (log_incidence_SEIR[i] == max_log_incidence_SEIR)
            {
                max_location_SEIR = i;
                break;
            }
        }

        double min_log_incidence = *min_element(log_incidence.begin(), log_incidence.end());
        double min_log_incidence_SEIR = *min_element(log_incidence_SEIR.begin(), log_incidence_SEIR.end());
        int min_location;
        int min_location_SEIR;

        for (i = 0; i < M - 1; i++)
        {
            if (log_incidence[i] == min_log_incidence)
            {
                min_location = i;
                break;
            }
        }
        for (i = 0; i < M - 1; i++)
        {
            if (log_incidence_SEIR[i] == min_log_incidence_SEIR)
            {
                min_location_SEIR = i;
                break;
            }
        }
        vector<double> least_square_data_incidence(max_location);
        for (i = 0; i < max_location - 1; i++)
        {
            least_square_data_incidence[i] = log_incidence[i];
        }

        vector<double> least_square_data_incidence_SEIR(max_location_SEIR);
        for (i = 0; i < max_location_SEIR - 1; i++)
        {
            least_square_data_incidence_SEIR[i] = log_incidence_SEIR[i];
        }

        vector<double> least_square_data_event_time_SIR(max_location);
        for (i = 0; i < max_location - 1; i++)
        {
            least_square_data_event_time_SIR[i] = event_time_SIR[i];
        }

        vector<double> least_square_data_event_time_SEIR(max_location_SEIR);
        for (i = 0; i < max_location_SEIR - 1; i++)
        {
            least_square_data_event_time_SEIR[i] = event_time_SEIR[i];
        }

        double sum_least_square_data_incidence{accumulate(least_square_data_incidence.begin(), least_square_data_incidence.end(), 0)};
        double sum_least_square_data_event_time_SIR{accumulate(least_square_data_event_time_SIR.begin(), least_square_data_event_time_SIR.end(), 0)};
        double mean_least_square_data_incidence{sum_least_square_data_incidence / max_location};
        double mean_least_square_data_event_time_SIR{sum_least_square_data_event_time_SIR / max_location};

        double sum_least_square_data_incidence_SEIR{accumulate(least_square_data_incidence_SEIR.begin(), least_square_data_incidence_SEIR.end(), 0)};
        double sum_least_square_data_event_time_SEIR{accumulate(least_square_data_event_time_SEIR.begin(), least_square_data_event_time_SEIR.end(), 0)};
        double mean_least_square_data_incidence_SEIR{sum_least_square_data_incidence_SEIR / max_location_SEIR};
        double mean_least_square_data_event_time_SEIR{sum_least_square_data_event_time_SEIR / max_location_SEIR};

        vector<double> dist_mean_incidence(max_location);
        vector<double> dist_mean_event_time_SIR(max_location);
        vector<double> dist_mean_event_time_SIR_squared(max_location);
        vector<double> multiply_dist_incidence_event_time_SIR(max_location);

        vector<double> dist_mean_incidence_SEIR(max_location_SEIR);
        vector<double> dist_mean_event_time_SEIR(max_location_SEIR);
        vector<double> dist_mean_event_time_SEIR_squared(max_location_SEIR);
        vector<double> multiply_dist_incidence_event_time_SEIR(max_location_SEIR);

        dist_mean_incidence = least_square_data_incidence - mean_least_square_data_incidence;
        dist_mean_event_time_SIR = least_square_data_event_time_SIR - mean_least_square_data_event_time_SIR;
        dist_mean_event_time_SIR_squared = dist_mean_event_time_SIR * dist_mean_event_time_SIR;
        multiply_dist_incidence_event_time_SIR = dist_mean_event_time_SIR * dist_mean_incidence;

        dist_mean_incidence_SEIR = least_square_data_incidence_SEIR - mean_least_square_data_incidence_SEIR;
        dist_mean_event_time_SEIR = least_square_data_event_time_SEIR - mean_least_square_data_event_time_SEIR;
        dist_mean_event_time_SEIR_squared = dist_mean_event_time_SEIR * dist_mean_event_time_SEIR;
        multiply_dist_incidence_event_time_SEIR = dist_mean_event_time_SEIR * dist_mean_incidence_SEIR;

        double sum_multiply_dist_incidence_event_time_SIR{accumulate(multiply_dist_incidence_event_time_SIR.begin(), multiply_dist_incidence_event_time_SIR.end(), 0)};
        double sum_dist_mean_event_time_SIR_squared{accumulate(dist_mean_event_time_SIR_squared.begin(), dist_mean_event_time_SIR_squared.end(), 0)};

        double sum_multiply_dist_incidence_event_time_SEIR{accumulate(multiply_dist_incidence_event_time_SEIR.begin(), multiply_dist_incidence_event_time_SEIR.end(), 0)};
        double sum_dist_mean_event_time_SEIR_squared{accumulate(dist_mean_event_time_SEIR_squared.begin(), dist_mean_event_time_SEIR_squared.end(), 0)};

        double r_growth_rate{sum_multiply_dist_incidence_event_time_SIR / sum_dist_mean_event_time_SIR_squared};

        double doubling_time{log(2) / log(1 + r_growth_rate / 100)};

        double r_growth_rate_SEIR{sum_multiply_dist_incidence_event_time_SEIR / sum_dist_mean_event_time_SEIR_squared};

        double doubling_time_SEIR{log(2) / log(1 + r_growth_rate_SEIR / 100)};

        cout << "| "
             << setw(10)
             << reproduction_number[j]
             << " | "
             << setw(10)
             << r_growth_rate
             << " | "
             << setw(10)
             << doubling_time
             << " | "
             << setw(10)
             << reproduction_number[j]
             << " | "
             << setw(10)
             << r_growth_rate_SEIR
             << " | "
             << setw(10)
             << doubling_time_SEIR
             << " |" << endl;
    }

    cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}