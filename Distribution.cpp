#include "stdafx.h"
#include "Distribution.h"

static std::pair<int, double> lastP;


double Distribution::getLambda() const {
	return lambda;
}

double Distribution::P(unsigned int n) const {
	if (lastP.first == n - 1) {
		lastP.second = lastP.second*lambda / n;
	}
	else {
		lastP.second = exp(-lambda)*pow(lambda, n) / tgamma(n + 1);
	}
	lastP.first = n;
	return lastP.second;
}

void Distribution::setLambda(double l_) {
	lambda = l_;
	lastP = std::pair<int, double>(-2, 0);
}

Distribution::Distribution() : lambda(1) { lastP = std::pair<int, double>(-2, 0); };