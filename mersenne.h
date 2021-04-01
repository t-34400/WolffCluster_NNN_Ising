#pragma once
#include <random>

namespace mersenne
{
	std::mt19937 mt;

	bool getTF();
	double getProbability();
}