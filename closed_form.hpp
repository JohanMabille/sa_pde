#ifndef CLOSED_FORM_HPP
#define CLOSED_FORM_HPP

#include <vector>

namespace dauphine
{
    double vanilla_payoff(double fwd, double strike, bool is_call);
    double bs_time_value(double fwd, double strike, double volatility, double maturity);
    double bs_price(double fwd, double strike, double volatility, double maturity, bool is_call);

    std::vector<double> vanilla_payoff(const std::vector<double>& fwd, double strike, bool is_call);
    std::vector<double> bs_time_value(const std::vector<double>& fwd, double strike, double volatility, double maturity);
    std::vector<double> bs_price(const std::vector<double>& fwd, double strike, double volatility, double maturity, bool is_call);
}

#endif
