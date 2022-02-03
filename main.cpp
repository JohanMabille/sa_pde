#include <iostream>
#include "closed_form.hpp"
#include "BS_Fixed.hpp"
#include "VanillaOption.hpp"
#include "BS_Param.hpp"
#include "CN_Scheme.hpp"


namespace dauphine {
	void price()
	{
            // Why static?
		static double sigma = 0.20;
		static double spot = 100.;
		static double T = 0.0833;
		static double strike = 100;
		static double r = 0.;

		cout << "BS Closed Form Call Price: " << bs_price(spot, strike, sigma, T, true) << endl;

		BSModel Model(spot, r, sigma);

		double low = 0.0, upper = 2.0 * spot;
		Put EuropeanPut(strike, T, low, upper);
		Call EuropeanCall(strike, T, low, upper);

		int imax = 200, jmax = 2000;

		BS_Param BSPDE(&Model, &EuropeanPut);
		BS_Param BSPDE2(&Model, &EuropeanCall);

		//Theta de la méthode Crank Nickolson:
		double theta = 0.5;

		CN_Scheme Method(&BSPDE, imax, jmax, theta);
		CN_Scheme Method2(&BSPDE2, imax, jmax, theta);

		Method.SolvePDE();
		Method2.SolvePDE();


		cout << "Put Price = " << Method.v(0.0, spot) << endl;
		cout << "Call Price = " << Method2.v(0.0, spot) << endl;

		double DeltaCall_value = EuropeanCall.DeltaCall(spot, strike, r, sigma, T);
		double GammaCall_value = EuropeanCall.GammaCall(spot, strike, r, sigma, T);
		double VegaCall_value = EuropeanCall.VegaCall(spot, strike, r, sigma, T);
		double ThetaCall_value = EuropeanCall.ThetaCall(spot, strike, r, sigma, T);


		cout << "Call delta: " << DeltaCall_value << endl;
		cout << "Call gamma: " << GammaCall_value << endl;
		cout << "Call vega: " << VegaCall_value << endl;
		cout << "Call theta: " << ThetaCall_value << endl;

	}

}

int main()
{
	dauphine::price();

	return 0;
}
