#include "closed_form.hpp"
#include <cmath>
#include <limits>
#include <algorithm>

namespace dauphine
{
    double ncdf(double x)
    {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }
    
    double vanilla_payoff(double fwd, double strike, bool is_call)
    {
        return std::max(is_call ? fwd - strike : strike - fwd, 0.);
    }

    double bs_time_value(double fwd, double strike, double volatility, double maturity)
    {
        if(strike == 0.)
        {
            return 0.;
        }
        else
        {
            double stddev = volatility * std::sqrt(maturity);
            if(stddev == 0.)
            {
                return 0.;
            }
            double tmp = std::log(fwd / strike) / stddev;
            double d1 = tmp + 0.5 * stddev;
            double d2 = tmp - 0.5 * stddev;
            double res;
            if(fwd > strike)
            {
                res = strike * ncdf(-d2) - fwd * ncdf(-d1);
            }
            else
            {
                res = fwd * ncdf(d1) - strike * ncdf(d2);
            }
            if(res <= std::numeric_limits<double>::min())
            {
                res = 0.;
            }
            return res;
        }
    }

    double bs_price(double fwd, double strike, double volatility, double maturity, bool is_call)
    {
        return vanilla_payoff(fwd, strike, is_call) + bs_time_value(fwd, strike, volatility, maturity);
    }

    std::vector<double> vanilla_payoff(const std::vector<double>& fwd, double strike, bool is_call)
    {
        std::vector<double> res(fwd.size());
        for(std::size_t i = 0; i < fwd.size(); ++i)
        {
            res[i] = vanilla_payoff(fwd[i], strike, is_call);
        }
        return res;
    }

    std::vector<double> bs_time_value(const std::vector<double>& fwd, double strike, double volatility, double maturity)
    {
        std::vector<double> res(fwd.size());
        for(std::size_t i = 0; i < fwd.size(); ++i)
        {
            res[i] = bs_time_value(fwd[i], strike, volatility, maturity);
        }
        return res;
    }

    std::vector<double> bs_price(const std::vector<double>& fwd, double strike, double volatility, double maturity, bool is_call)
    {
        std::vector<double> res(fwd.size());
        for(std::size_t i = 0; i < fwd.size(); ++i)
        {
            res[i] = bs_price(fwd[i], strike, volatility, maturity, is_call);
        }
        return res;
    }
}

