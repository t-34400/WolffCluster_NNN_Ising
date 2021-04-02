#include "mersenne.h"
#include <ctime>
#include <random>

std::mt19937 mersenne::mt{ static_cast<std::mt19937::result_type>(time(nullptr)) };

bool mersenne::getRandomBool()
{
	return std::uniform_int_distribution<>{0, 1}(mt);
}

int mersenne::getRandomInt(int min, int max)
{
	return std::uniform_int_distribution<>{min, max}(mt);
}

double mersenne::getProbability()
{
	return std::uniform_real_distribution<>{0.0, 1.0}(mt);
}