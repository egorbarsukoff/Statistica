#include "stdafx.h"
#include "CommonRandom.h"

std::mt19937& CommonRandom::get_mt() {
	return mt;
}


double getu01() {
	return std::uniform_real_distribution<double>(0, 1)(CommonRandom::get_mt());
}