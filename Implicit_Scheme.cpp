#include "Implicit_Scheme.hpp"
#include "Matrix_Operators.hpp"
#include <cmath>

Vector Implicit_Scheme::w(int i)
{
   Vector w(FiniteDiff::get_jmax()+1);
   w[1]=D(i,1)+A(i,1)*fl(i)-E(i,1)*fl(i-1);
   for (int j=2;j<FiniteDiff::get_jmax()-1;j++) w[j]=D(i,j);
   w[FiniteDiff::get_jmax()-1]=D(i,FiniteDiff::get_jmax()-1)+C(i,FiniteDiff::get_jmax()-1)*fu(i)-G(i,FiniteDiff::get_jmax()-1)*fu(i-1);
   return w;
}

Vector Implicit_Scheme::A(int i, Vector q)
{
   Vector p(FiniteDiff::get_jmax()+1);
   p[1]=B(i,1)*q[1]+C(i,1)*q[2];
   for (int j=2;j<FiniteDiff::get_jmax()-1;j++)
   {
      p[j]=A(i,j)*q[j-1]+B(i,j)*q[j]+C(i,j)*q[j+1];
   }
   p[FiniteDiff::get_jmax()-1]=A(i,FiniteDiff::get_jmax()-1)*q[FiniteDiff::get_jmax()-2]+B(i,FiniteDiff::get_jmax()-1)*q[FiniteDiff::get_jmax()-1];
   return p;
}

Vector Implicit_Scheme::LUDecomposition(int i, Vector q)
{
   Vector p(FiniteDiff::get_jmax()+1), r(FiniteDiff::get_jmax()+1), y(FiniteDiff::get_jmax()+1);
   r[1]=F(i,1);
   y[1]=q[1];
   for (int j=2;j<FiniteDiff::get_jmax();j++)
   {
      r[j]=F(i,j)-E(i,j)*G(i,j-1)/r[j-1];
      y[j]=q[j]-E(i,j)*y[j-1]/r[j-1];
   }
   p[FiniteDiff::get_jmax()-1]=y[FiniteDiff::get_jmax()-1]/r[FiniteDiff::get_jmax()-1];
   for (int j=FiniteDiff::get_jmax()-2; j>0; j--)
   {
      p[j]=(y[j]-G(i,j)*p[j+1])/r[j];
   }
   return p;
}

void Implicit_Scheme::SolvePDE()
{
   
   for (int j=0; j<=FiniteDiff::get_jmax(); j++) V[FiniteDiff::get_imax()][j]=f(j);
   for (int i=FiniteDiff::get_imax(); i>0; i--)
   {
      V[i-1]=LUDecomposition(i,A(i,V[i])+w(i));
      V[i-1][0]=fl(i-1);
      V[i-1][FiniteDiff::get_jmax()]=fu(i-1);
   }
}


