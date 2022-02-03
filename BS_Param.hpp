#ifndef BS_Param_HPP
#define BS_Param_HPP

#include "PDE.hpp"
#include "BS_Fixed.hpp"
#include "VanillaOption.hpp"

class BS_Param: public PDE
{
   private:
      BSModel* PtrModel;
      VanillaOption* PtrVanillaOption;

    public:
      BS_Param(BSModel* PtrModel_,VanillaOption* PtrVanillaOption_);
      ~BS_Param();

      // using override would help to see that these
      // methods are actually virtual
      double a(double t, double z);
      double b(double t, double z);
      double c(double t, double z);
      double d(double t, double z);

      double f(double z);
      double fl(double t);
      double fu(double t);
};

#endif

