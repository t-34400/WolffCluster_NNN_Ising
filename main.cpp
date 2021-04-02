#include "Ising.h"
#include "Wolff.h"
#include <iostream>

int main()
{
	Wolff wolff(0.44068679350977147, 0);
	
	for (int i{ 0 }; i < 20; i++)
	{
		std::cout << wolff.getMagnetization() << ' ' << wolff.getEnergy() << ' ' << wolff.getCorrelationInTime(1) << '\n';
		wolff.stepForward(1);
	}

	return 0;
}