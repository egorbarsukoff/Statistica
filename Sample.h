#pragma once
#include "Distribution.h"
#include <climits>


/// Abstract sample of the simulated observations
class Sample {
protected:
	/// Array of observation
	unsigned int* x;
	/// Minimum value in the Sample
	unsigned int minValue;
	/// Maximum value in the Sample
	unsigned int maxValue;
	/// Sammple size
	size_t n;
	/// Simulate one observation
	virtual unsigned int simulate(const Distribution &d) = 0;
	
public:
	/// Constructor
	Sample() : minValue(0), maxValue(0), x(nullptr), n(0) {}
	/// Simulates sample
	void modeling(const Distribution &d, size_t n_);
	/// Returns the size of the Sample
	size_t getN() const;
	/// Returns the maximum value in the Sample
	unsigned int getMax() const;
	/// Returns the minimum value in the Sample
	unsigned int getMin() const;
	/// Returns the i-th observation
	unsigned int getX (size_t i) const;
	/// Destructor
	virtual ~Sample();
};

