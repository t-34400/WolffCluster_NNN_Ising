#pragma once
#include <random>

namespace mersenne
{
	extern std::mt19937 mt;

	bool getTF();
	double getProbability();
}