#pragma once
#include <random>

namespace mersenne
{
	extern std::mt19937 mt;

	bool getRandomBool();
	int getRandomInt(int min, int max);
	double getProbability();
}