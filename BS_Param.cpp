#include "BS_Param.hpp"
#include <cmath>

BS_Param::BS_Param(BSModel* PtrModel_,VanillaOption* PtrVanillaOption_)
{
   PtrModel=PtrModel_; PtrVanillaOption=PtrVanillaOption_;
   T =PtrVanillaOption->VanillaOption::get_T();
   xl=PtrVanillaOption->VanillaOption::get_low();
   xu=PtrVanillaOption->VanillaOption::get_upper();
}

BS_Param::~BS_Param()
{}

double BS_Param::a(double t, double z)
{
   return -0.5*pow(PtrModel->sigma*z,2.0);
}

double BS_Param::b(double t, double z)
{
   return -PtrModel->r*z;
}

double BS_Param::c(double t, double z)
{
   return PtrModel->r;
}

double BS_Param::d(double t, double z)
{
   return 0.0;
}

double BS_Param::f(double z)
{
   return PtrVanillaOption->Payoff(z);
}

double BS_Param::fl(double t)
{
   return PtrVanillaOption->LowerBdCond(PtrModel,t);
}

double BS_Param::fu(double t)
{
   return PtrVanillaOption->UpperBdCond(PtrModel,t);
}


