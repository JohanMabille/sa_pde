#ifndef CN_Scheme_HPP
#define CN_Scheme_HPP

#include "Implicit_Scheme.hpp"

class CN_Scheme: public Implicit_Scheme
{
    private:
        double theta = 0.5;
    public:
      CN_Scheme(PDE* PtrPDE_, int imax_, int jmax_, double theta_)
          : Implicit_Scheme(PtrPDE_, imax_, jmax_) {theta = theta_;}

      ~CN_Scheme(){}

      double get_theta() { return theta; }

      double A(int i, int j)
      {
          return (1.0 - theta) * FiniteDiff::get_dt() * (b(i - theta, j) / 2.0 - a(i - theta, j) / FiniteDiff::get_dx()) / FiniteDiff::get_dx();
      }
      double B(int i, int j)
      {
          return 1.0 + (1.0 - theta) * FiniteDiff::get_dt() * (2.0 * a(i - theta, j) / (FiniteDiff::get_dx() * FiniteDiff::get_dx()) - c(i - theta, j));
      }
      double C(int i, int j)
      {
          return -(1.0 - theta) * FiniteDiff::get_dt() * (b(i - theta, j) / 2.0 + a(i - theta, j) / FiniteDiff::get_dx()) / FiniteDiff::get_dx();
      }

      double D(int i, int j) { return -FiniteDiff::get_dt() * d(i - theta, j); }

      double E(int i, int j)
      {
          return -theta * FiniteDiff::get_dt() * (b(i - theta, j) / 2.0 - a(i - theta, j) / FiniteDiff::get_dx()) / FiniteDiff::get_dx();
      }
      double F(int i, int j)
      {
          return 1.0 - theta * FiniteDiff::get_dt() * (2.0 * a(i - theta, j) / (FiniteDiff::get_dx() * FiniteDiff::get_dx()) - c(i - theta, j));
      }
      double G(int i, int j)
      {
          return theta * FiniteDiff::get_dt() * (b(i - theta, j) / 2.0 + a(i - theta, j) / FiniteDiff::get_dx()) / FiniteDiff::get_dx();
      }
};

#endif


