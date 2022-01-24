#ifndef Implicit_Scheme_HPP
#define Implicit_Scheme_HPP

#include "FiniteDiff.hpp"
#include "Matrix_Operators.hpp"

class Implicit_Scheme: public FiniteDiff
{
   public:
      Implicit_Scheme(PDE* PtrPDE_,int imax_,int jmax_)
         : FiniteDiff(PtrPDE_, imax_, jmax_){}

      Vector w(int i);
      Vector A(int i, Vector q);

      Vector LUDecomposition(int i,Vector q);

      void SolvePDE();

    private:
        virtual double A(int i, int j) = 0;
        virtual double B(int i, int j) = 0;
        virtual double C(int i, int j) = 0;
        virtual double D(int i, int j) = 0;
        virtual double E(int i, int j) = 0;
        virtual double F(int i, int j) = 0;
        virtual double G(int i, int j) = 0;
};
#endif

