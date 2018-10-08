#pragma once

#include <random>


class CommonRandom {
	static std::mt19937 mt;
public:
	static std::mt19937& get_mt();
};

double getu01();

