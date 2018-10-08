#pragma once
#include "Histogram.h"


///Histogram that gives the observed and theoretical frequencies for given Sample and Distribution
class DistributionHistogram :
	public Histogram {
	double maxVal; 
public:
	/// Returns maxVal
	double getMaxVal() const; 
	///Returns the minimum value of the sample
	size_t getMinX() const; 
	///Returns the maximum value of the sample
	size_t getMaxX() const; 
	/// Returns theoritical frecuency for i
	double getTheor(size_t i) const; 
	/// Returns observed frecuency for i
	double getObs(size_t i) const; 
	///brief Constructor
	DistributionHistogram(const Sample *_x, const Distribution &_d); 
	/// Move constructor
	DistributionHistogram(DistributionHistogram&& old) :
		Histogram(old), maxVal(old.maxVal) {} 
	///Copy constructor
	DistributionHistogram(const Histogram& h); 
	DistributionHistogram() = default;
	///Move operator
	DistributionHistogram& operator=(DistributionHistogram&& hh); 
};

