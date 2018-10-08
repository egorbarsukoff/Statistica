#include "stdafx.h"
#include "Sample.h"



Sample::~Sample() {
	delete[] x;
}

size_t Sample::getN() const {
	return n;
}

void Sample::modeling(const Distribution &d, size_t n_) {
	if (x != nullptr) 
		delete[] x;
	x = new unsigned int[n_];
	n = n_;
	minValue = UINT_MAX;
	maxValue = 0;
	for (int i = 0; i < n; ++i) {
		x[i] = simulate(d);
		if (minValue > x[i])
			minValue = x[i];
		if (maxValue < x[i])
			maxValue = x[i];
	}
}

unsigned int Sample::getX (size_t i) const {
	if (i < n)
		return x[i];
	return -1;
}

unsigned int Sample::getMax() const {
	return maxValue;
}

unsigned int Sample::getMin() const {
	return minValue;
}
