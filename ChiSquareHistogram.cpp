#include "stdafx.h"
#include "ChiSquareHistogram.h"

void ChiSquareHistogram::calcChiSquare() {
	double sum = 0;
	for (size_t i = 0; i < n; ++i) {
		assert(theorFrec[i] != 0);
		sum += pow(theorFrec[i] - obsFrec[i], 2) / theorFrec[i];
	}
	sum *= dh->getSampleSize();
	chiSquare = sum;
}

void ChiSquareHistogram::calcPValue() {
	pValue = 1-pChi(chiSquare, n - 1);
}

void ChiSquareHistogram::grouping() {
	const int MIN_VAL = 5;
	int currpos;
	for (currpos = 0; currpos < n; ++currpos) {
		for (int i = currpos+1; i < n && theorFrec[currpos] * x->getN() < 5; ++i) {
			theorFrec[currpos] += theorFrec[i];
			theorFrec[i] = 0;
			obsFrec[currpos] += obsFrec[i];
			obsFrec[i] = 0;
		}
		if (theorFrec[currpos] == 0)
			break;
	}
	if (theorFrec[currpos - 1] * x->getN() < 5 && currpos > 1) {
		theorFrec[currpos-2] += theorFrec[currpos-1];
		theorFrec[currpos-1] = 0;
		obsFrec[currpos-2] += obsFrec[currpos-1];
		obsFrec[currpos-1] = 0;
		--currpos;
	}
	n = currpos;
}

ChiSquareHistogram::ChiSquareHistogram(const DistributionHistogram && _dh) : 
		Histogram(_dh) {
	dh = new DistributionHistogram(*this);
	grouping();
	calcChiSquare();
	calcPValue();
}

ChiSquareHistogram::~ChiSquareHistogram() {
	delete dh;
}

const DistributionHistogram & ChiSquareHistogram::getDistributionHistogram() const {
	return *dh;
}

double ChiSquareHistogram::getChiSquare() const{
	return chiSquare;
}

double ChiSquareHistogram::getPValue() const{
	return pValue;
}

size_t ChiSquareHistogram::getDoF() const {
	return n-1;
}

