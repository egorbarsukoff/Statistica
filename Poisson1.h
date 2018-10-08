#pragma once
#include "Sample.h"
#include "CommonRandom.h"


/// Poisson1 simulated Sample
class Poisson1 :
	public Sample {
protected:
	/// Simulate one observation
	unsigned int simulate(const Distribution &d) override;
public:
	Poisson1() = default;
	~Poisson1() = default;
};

