#pragma once

#include <chrono>
#include "Poisson1.h"
#include "Poisson2.h"


/// Dependence time of sumulation on the distribution parameter
class ParametersTime {
	double *time1; 
	double *time2; 
	double a;
	double b;
	double step;
	double maxTime;
	size_t n, sampleSize;
	double simulateTime(Sample* s, const Distribution& d); 
public:
	/// Calculating the dependecies between the Distribution paramener and time of simulation
	void simulate();  
	/// Returns the numbers of time counts for every method
	size_t getN() const; 
	/// Returns the i-th time count for Poisson1
	double getTime1(size_t i) const; 
	/// Returns the i-th time count for Poisson2
	double getTime2(size_t i) const; 
	/// Returns the size of Sample
	double getSampleSize() const; 
	/// Returns the max value
	double getMax() const; 
	/// Return the lower limit of the parameter
	double getA() const; 
	/// Retrns the upper limits of the parameter
	double getB() const; 
	/// Returns the step of the parameter
	double getStep() const; 
	/// Constructor
	ParametersTime(double _a, double _b, double _step, size_t _sampleSize); 
	/// Destructor
	~ParametersTime(); 
};

