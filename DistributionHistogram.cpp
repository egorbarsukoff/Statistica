#include "stdafx.h"
#include "DistributionHistogram.h"


double DistributionHistogram::getMaxVal() const {
	return maxVal;
}

size_t DistributionHistogram::getMinX() const {
	return minX;
}

size_t DistributionHistogram::getMaxX() const {
	return maxX;
}

double DistributionHistogram::getTheor(size_t i) const {
	return theorFrec[i-x->getMin()];
}

double DistributionHistogram::getObs(size_t i) const {
	return obsFrec[i-x->getMin()];
}

DistributionHistogram::DistributionHistogram(const Sample *_x, const Distribution &_d) :
	Histogram(_x, _d), maxVal(0){
	for (int i = 0; i < n; ++i) {
		theorFrec[i] /= x->getN();
		obsFrec[i] /= x->getN();
		if (maxVal < max(obsFrec[i], theorFrec[i]))
			maxVal = max(obsFrec[i], theorFrec[i]);
	}
}


DistributionHistogram::DistributionHistogram(const Histogram & h) : Histogram(h) {
	for (int i = 0; i < n; ++i) {
		if (maxVal < max(obsFrec[i], theorFrec[i]))
			maxVal = max(obsFrec[i], theorFrec[i]);
	}
}

DistributionHistogram & DistributionHistogram::operator=(DistributionHistogram && hh) {
	if (this == &hh)
		return *this;
	maxVal = hh.maxVal;
	Histogram::operator=(std::move(hh));
	
}
