#pragma once
#include "Histogram.h"
#include "PROBDIST.H"
#include "DistributionHistogram.h"


/// Histogram for calculate chi-square and p-value
class ChiSquareHistogram :
	public Histogram {
	const DistributionHistogram * dh; 
	double chiSquare; 
	double pValue; 
	void calcChiSquare();
	void calcPValue();
	void grouping();
public:
	/// Constructor
	ChiSquareHistogram(const Sample *_x, const Distribution &_d) :
		ChiSquareHistogram(DistributionHistogram(_x, _d)) {} 
	/// Constructor
	ChiSquareHistogram(const DistributionHistogram&& _dh); 
	///Destructor
	~ChiSquareHistogram(); 
	/// Returns the original Histogram before grouping
	const DistributionHistogram& getDistributionHistogram() const; 
	/// Returns chi-square statistic
	double getChiSquare() const;
	/// Returns p-value
	double getPValue() const; 
	/// Returns degrees of freedom for this statistic
	size_t getDoF() const; 
};

