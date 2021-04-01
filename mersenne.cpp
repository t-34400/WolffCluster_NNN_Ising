#include "mersenne.h"
#include <ctime>
#include <random>

std::mt19937 mersenne::mt{ static_cast<std::mt19937::result_type>(time(nullptr)) };

bool mersenne::getTF()
{
	return std::uniform_int_distribution<>{0, 1}(mt);
}

double mersenne::getProbability()
{
	return std::uniform_real_distribution<>{0.0, 1.0}(mt);
}