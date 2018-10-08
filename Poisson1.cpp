#include "stdafx.h"
#include "Poisson1.h"



unsigned int Poisson1::simulate(const Distribution &d) {
	double lambda = d.getLambda();
	unsigned int k = 0;
	double t = exp(-lambda);
	double s = t;
	double a = getu01();
	while (true) {
		if (a <= s)
			return k;
		else {
			++k;
			t = lambda * t / k;
			s += t;
		}
	}
}
