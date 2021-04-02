#include "Ising.h"
#include <iostream>

int main()
{
	if (true ^ true)
		std::cout << "1 yes.\n";
	if (true ^ false)
		std::cout << "2 yes\n";
	if (false ^ true)
		std::cout << "3 yes\n";
	if (false ^ false)
		std::cout << "4 yes\n";
	return 0;
}