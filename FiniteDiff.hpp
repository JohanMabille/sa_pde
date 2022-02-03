#ifndef FiniteDiff_HPP
#define FiniteDiff_HPP
#include <vector>
#include "PDE.hpp"

// please, no!
using namespace std;
typedef vector<double> Vector;

class FiniteDiff
{
  private:
      PDE* PtrPDE;
      int imax, jmax;
      double dx, dt;
      


      
  public:

      vector<Vector> V;
      FiniteDiff(PDE* PtrPDE_, int imax_, int jmax_);
      ~FiniteDiff();
      int get_jmax() { return jmax; }
      int get_imax() { return imax; }
      double get_dx() { return dx; }
      double get_dt() { return dt; }
      vector<Vector> get_V() { return V; }
      
      double t(double i){return dt*i;}
      double x(int j){return PtrPDE->xl+dx*j;}

      double a(double i,int j){return PtrPDE->a(t(i),x(j));}
      double b(double i,int j){return PtrPDE->b(t(i),x(j));}
      double c(double i,int j){return PtrPDE->c(t(i),x(j));}
      double d(double i,int j){return PtrPDE->d(t(i),x(j));}

      double f (int j){return PtrPDE->f(x(j));}
      double fu(int i){return PtrPDE->fu(t(i));}
      double fl(int i){return PtrPDE->fl(t(i));}

      double v(double t,double x);
};

#endif


