#pragma once
#include <ctime>
#include <random>

namespace mersenne
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(time(nullptr)) };

	bool getTF()
	{
		static std::uniform_int_distribution<bool> tf(0, 1);
		return tf(mt);
	}

	double getProbability()
	{
		static std::uniform_real_distribution<double> prob(0.0, 1.0);
		return prob(mt);
	}
}