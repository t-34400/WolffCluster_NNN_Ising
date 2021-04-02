#include "Ising.h"
#include "Wolff.h"
#include <iostream>

int main()
{
	Ising ising;
	Wolff wolff(ising, 0.44068679350977147, 0);
	
	wolff.stepForward(1);

	return 0;
}