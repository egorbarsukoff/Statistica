#pragma once
#include "Sample.h"
#include "CommonRandom.h"


/// Poisson2 simulated Sample
class Poisson2 :
	public Sample {
protected:
	/// Simulate one observation
	unsigned int simulate(const Distribution &d) override;
public:
	Poisson2() = default;
	~Poisson2() = default;
};

