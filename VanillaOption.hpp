#ifndef VanillaOption_HPP
#define VanillaOption_HPP
#define _USE_MATH_DEFINES


#include <iostream>
#include <cmath>
#include <algorithm>
#include <math.h>

#include "BS_Fixed.hpp"

class VanillaOption
{
    protected:
        double T, low, upper;
    public:
      
      virtual double Payoff(double z)=0;
      virtual double UpperBdCond
         (BSModel* PtrModel, double t)=0;
      virtual double LowerBdCond
         (BSModel* PtrModel, double t)=0;

      double get_T() const;
      double get_low() const;
      double get_upper() const;


       // Computing Normal probability density function
      double norm_pdf(const double& x) {
          return (1.0 / pow(2 * M_PI, 0.5)) * exp(-0.5 * x * x);
      }

      // Cumulative distribution function
      double norm_cdf(const double& x) {
          double k = 1.0 / (1.0 + 0.2316419 * x);
          double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

          if (x >= 0.0) {
              return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)) * exp(-0.5 * x * x) * k_sum));
          }
          else {
              return 1.0 - norm_cdf(-x);
          }
      }

      // Calculating d1 and d2
      double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
          return (log(S / K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (pow(T, 0.5)));
      }

};



class Call : public VanillaOption
{
private:
    double K;
public:
    
    Call(double K_, double T_, double low_, double upper_)
    {
        K = K_; T = T_; low = low_; upper = upper_;
    }

    ~Call();

    double Payoff(double z);
    double UpperBdCond(BSModel* PtrModel, double t);
    double LowerBdCond(BSModel* PtrModel, double t);
    double get_Kcall() const;


    // Calculating Greeks for a call 

    // Delta
    double DeltaCall(const double S, const double K, const double r, const double v, const double T) {
        return norm_cdf(d_j(1, S, K, r, v, T));
    }

    // Gamma
    double GammaCall(const double S, const double K, const double r, const double v, const double T) {
        return norm_pdf(d_j(1, S, K, r, v, T)) / (S * v * sqrt(T));
    }

    // Vega
    double VegaCall(const double S, const double K, const double r, const double v, const double T) {
        return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T);
    }

    // Theta
    double ThetaCall(const double S, const double K, const double r, const double v, const double T) {
        return -S * norm_pdf(d_j(1, S, K, r, v, T)) * v / (2 * sqrt(T)) - r * K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
    }
};

class Put: public VanillaOption
{
private:
    double K ;
public:

      Put(double K_, double T_, double low_, double upper_)
         {K=K_; T=T_; low=low_; upper=upper_;}
      ~Put();
      double Payoff(double z);
      double UpperBdCond(BSModel* PtrModel, double t);
      double LowerBdCond(BSModel* PtrModel, double t);
      double get_Kput() const;

      //Calculating greeks for a put

      // Delta
      double DeltaPut(const double S, const double K, const double r, const double v, const double T) {
          return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
      }

      // Gamma
      double GammaPut(const double S, const double K, const double r, const double v, const double T) {
          return norm_pdf(d_j(1, S, K, r, v, T)) / (S * v * sqrt(T));
      }

      // Vega
      double VegaPut(const double S, const double K, const double r, const double v, const double T) {
          return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T);
      }

      // Theta
      double ThetaPut(const double S, const double K, const double r, const double v, const double T) {
          return -S * norm_pdf(d_j(1, S, K, r, v, T)) * v / (2 * sqrt(T)) + r * K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
      }
};





#endif
