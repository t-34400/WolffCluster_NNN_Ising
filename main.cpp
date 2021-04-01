#include "Ising.h"
#include "isingConstant.h"
#include <iostream>

int main()
{
	Ising ising{};
	std::cout << ising.getValue(0) << '\n';
	ising.flip(0);
	std::cout << ising.getValue(0) << '\n';

	return 0;
}