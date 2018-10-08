#include "stdafx.h"
#include "Histogram.h"


size_t Histogram::getSampleSize() const {
	return x->getN();
}

size_t Histogram::getN() const {
	return n;
}

const Distribution & Histogram::getDistribution() const {
	return *d;
}

Histogram::Histogram(const Sample *_x, const Distribution &_d) :
	x(_x), d(&_d) {
	setLimits();
	theorFrec = new double[n];
	obsFrec = new double[n];
	setObs();
	setTheor();
	;
}

Histogram::Histogram(const Histogram & old) : x(old.x), d(old.d), n(old.n), maxX(old.maxX), minX(old.minX) {
	theorFrec = new double[n];
	obsFrec = new double[n];
	memcpy(theorFrec, old.theorFrec, n * sizeof(double));
	memcpy(obsFrec, old.obsFrec, n * sizeof(double));
}

Histogram::Histogram(Histogram &&old) :
	theorFrec(old.theorFrec), obsFrec(old.obsFrec), x(old.x), d(old.d), n(old.n), maxX(old.maxX), minX(old.minX) {
	old.theorFrec = nullptr;
	old.obsFrec = nullptr;
}


Histogram::~Histogram() {
	delete[] theorFrec;
	delete[] obsFrec;
}

Histogram & Histogram::operator=(Histogram && h) {
	if (this == &h)
		return *this;
	delete[] this->theorFrec;
	delete[] this->obsFrec;
	this->theorFrec = h.theorFrec;
	this->obsFrec = h.obsFrec;
	h.theorFrec = nullptr;
	h.obsFrec = nullptr;
	x = h.x;
	d = h.d;
	n = h.n;
	maxX = h.maxX;
	minX = h.minX;
}

void Histogram::setObs() {
	for (int i = 0; i < n; ++i) {
		obsFrec[i] = 0;
	}
	for (int i = 0; i < x->getN(); ++i) {
		assert(x->getX(i) - minX < n);
		++obsFrec[x->getX(i) - minX];
	}
}


void Histogram::setTheor() {
	double sum = 0;
	for (int i = 0; i <= minX; ++i) {
		sum += d->P(i)* x->getN();
	}
	theorFrec[0] = sum;
	for (int i = 1; i < n-1; ++i) {
		if (i != n-1) {
			theorFrec[i] = d->P(i + minX) * x->getN();
			sum += theorFrec[i];
		}			
	}
	theorFrec[n - 1] = x->getN() - sum;
}

void Histogram::setLimits() {
	double tail = 0;
	size_t i = 0;
	for (; tail*x->getN() < 5; ++i)
		tail += d->P(i);
	minX = min(x->getMin(), i);
	for (; (1-tail)*x->getN() > 5; ++i)
		tail += d->P(i);
	maxX = max(x->getMax(), i);
	n = maxX - minX +1;
}
