#include "VanillaOption.hpp"
#include <cmath>

double VanillaOption::get_T() const
{
	return T;
}

double VanillaOption::get_upper() const
{
	return upper;
}

double VanillaOption::get_low() const
{
	return low;
}

Call::~Call()
{}

double Call::get_Kcall() const
{
	return K;
}


double Call::Payoff(double z)
{
	if (z < K) return 0.0;
	return z - K;
}

double Call::UpperBdCond(BSModel* PtrModel, double t)
{
	return VanillaOption::get_upper() - K * exp(-PtrModel->r * (VanillaOption::get_T() - t));
}

double Call::LowerBdCond(BSModel* PtrModel, double t)
{
	return VanillaOption::get_low();
}

Put::~Put()
{}

double Put::get_Kput() const
{
	return K;
}

double Put::Payoff(double z)
{
   if (K<z) return 0.0;
   return K-z;
}

double Put::UpperBdCond(BSModel* PtrModel, double t)
{
   return 0.0;
}

double Put::LowerBdCond(BSModel* PtrModel, double t)
{
   return K*exp(-PtrModel->r*(VanillaOption::get_T() -t));
}






