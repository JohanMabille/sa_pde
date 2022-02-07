#ifndef BSModelFixed_HPP
#define BSModelFixed_HPP

// Ultimate evil!!! and totally useless here since you
// don't use any std type
using namespace std;

// no need for these includes
#include <vector>
#include <cstdlib>



class BSModel
{
   public:
      double S0, r, sigma;
      BSModel(double S0_, double r_, double sigma_)
         {S0 = S0_; r = r_; sigma = sigma_;}
      ~BSModel(){}

};

#endif


