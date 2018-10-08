#pragma once

#include <cmath>
#include <utility>

/// Describes the poisson distribution
class Distribution
{
	double lambda; 
public:
	/// Default constructor
	Distribution(); 
	/// Returns lambda parameter
	double getLambda() const; 
	/// Change lambda parameter
	void setLambda(double l_); 
	/// Returns the propability P(xi = n)
	double P(unsigned int n) const; 
};

