#include "stdafx.h"
#include "Poisson2.h"

//std::mt19937 CommonRandom::mt;

unsigned int Poisson2::simulate(const Distribution &d) {
	double lambda = d.getLambda();
	double t = 1, l = exp(-lambda), a;
	int n = 0;
	while (true) {
		a = getu01();
		t = t * a;
		if (t < l)
			return n;
		else
			++n;
	}
}

