#include "stdafx.h"
#include "PValueDistribution.h"


PValueDistribution::PValueDistribution(Sample& _s, const Distribution& _d0, const Distribution& _d1, size_t _nCol, size_t _sampleSize, unsigned int _repeats) :
		s(&_s), d0(&_d0), d1(&_d1), nCol(_nCol), repeats(_repeats), sampleSize(_sampleSize) {
	pValDistribution = new unsigned int[nCol+1];
	for (size_t i = 0; i < nCol; ++i)
		pValDistribution[i] = 0;
}

size_t PValueDistribution::getNCol() const{
	return nCol;
}

double PValueDistribution::getH0Lambda() const {
	return d0->getLambda();
}

double PValueDistribution::getH1Lambda() const {
	return d1->getLambda();
}

unsigned int PValueDistribution::getSampleSize() const{
	return sampleSize;
}

unsigned int PValueDistribution::getRepeats() const {
	return repeats;
}


PValueDistribution::~PValueDistribution() {
	delete[] pValDistribution;
}

void PValueDistribution::simulate() {
	for (unsigned int i = 0; i < repeats; ++i) {
		s->modeling(*d1, sampleSize);
		addObs(ChiSquareHistogram(s, *d0).getPValue());
	}
	accumulateSum();
}

void PValueDistribution::addObs(double obs) {
	assert(obs <= 1);
	++pValDistribution[size_t(obs*nCol)];
}

void PValueDistribution::accumulateSum() {
	unsigned int sum = 0;
	for (size_t i = 0; i <= nCol; ++i) {
		sum += pValDistribution[i];
		pValDistribution[i] = sum;
	}
}

double PValueDistribution::operator()(double x) const{
	return (double)pValDistribution[size_t(x*nCol)] / repeats;
}
