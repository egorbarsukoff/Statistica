#pragma once

#include <functional>
#include "Sample.h"
#include "Distribution.h"

///Abstract histogram for emperical and theoretical frequencies.
class Histogram {
	void setLimits();
	void setObs();
	void setTheor(); 
protected:
	/// Move constructor
	Histogram(Histogram &&old); 
	/// The array that contain theoretical frequencies for a given Distribution
	double *theorFrec; 
	/// The array that contains observed frequencies for a given Sample
	double *obsFrec; 
	///  The Sample for which the Histogram was constructed
	const Sample* x; 
	///  The Distribution for which the Histogram was constructed
	const Distribution* d; 
	/// Maximum value 
	size_t maxX;
	/// Minimum value
	size_t minX;
	/// Size of arrays
	size_t n;
public:
	/// Gives the size of the sample 
	size_t getSampleSize() const; 
	/// Gives the size of the arrays
	size_t getN() const; 
	/// Gives the Distribution of this Histogram
	const Distribution& getDistribution() const;  
	/// Constructor
	Histogram(const Sample *_x, const Distribution &_d); 
	/// Copy constructor
	Histogram(const Histogram &old); 
	
	virtual ~Histogram();
	/// Move operator
	Histogram& operator=(Histogram&& h); 

};

