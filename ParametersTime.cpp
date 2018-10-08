#include "stdafx.h"
#include "ParametersTime.h"




double ParametersTime::simulateTime(Sample * s, const Distribution & d) {
	auto begin = std::chrono::steady_clock::now();
	s->modeling(d, sampleSize);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - begin;
	return std::chrono::duration <double, std::milli>(diff).count();
}

void ParametersTime::simulate() {
	Sample *s = new Poisson1();
	Distribution d;
	for (size_t i = 0; i < n; ++i) {
		d.setLambda(a + i * step);
		time1[i] = simulateTime(s, d);
		if (maxTime < time1[i])
			maxTime = time1[i];
	}
	delete s;
	s = new Poisson2();
	for (size_t i = 0; i < n; ++i) {
		d.setLambda(a + i * step);
		time2[i] = simulateTime(s, d);
		if (maxTime < time2[i])
			maxTime = time2[i];
	}
	delete s;
}

size_t ParametersTime::getN() const{
	return n;
}

double ParametersTime::getTime1(size_t i) const{
	return time1[i];
}

double ParametersTime::getTime2(size_t i) const{
	return time2[i];
}

double ParametersTime::getSampleSize() const{
	return sampleSize;
}

double ParametersTime::getMax() const{
	return maxTime;
}

double ParametersTime::getA() const {
	return a;
}

double ParametersTime::getB() const {
	return b;
}

double ParametersTime::getStep() const {
	return step;
}

ParametersTime::ParametersTime(double _a, double _b, double _step, size_t _sampleSize) : 
a(_a), b(_b), step(_step), sampleSize(_sampleSize), n((b-a)/step+1), maxTime(0) {
	time1 = new double[n];
	time2 = new double[n];
}

ParametersTime::~ParametersTime() {
	delete[] time1;
	delete[] time2;
}
