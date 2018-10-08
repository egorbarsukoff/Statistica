#pragma once
#include "Sample.h"
#include "Distribution.h"
#include "ChiSquareHistogram.h"

/// Empirical distribution function of p-value
class PValueDistribution {
	size_t nCol, sampleSize;
	unsigned int repeats;
	unsigned int *pValDistribution;
	void addObs(double obs);
	void accumulateSum();
	Sample * s;
	const Distribution *d0, *d1;
public:
	/// Distribution function
	double operator() (double x) const;
	/// Constructor
	PValueDistribution(Sample& _s, const Distribution& _d0, const Distribution& _d1, size_t _nCol, size_t _sampleSize, unsigned int _repeats);
	/// Number of steps in empirical distribution function
	size_t getNCol() const;
	/// Theoretical distribution parameter
	double getH0Lambda() const;
	/// Observed distribution parameter
	double getH1Lambda() const;
	/// Size of each Sample
	unsigned int getSampleSize() const;
	/// Size of p-values sample
	unsigned int getRepeats() const;
	/// Calculates empirical distribution function
	void simulate();
	/// Destructor
	~PValueDistribution();
};

