#pragma once
#include "isingConstant.h"
#include <array>

class Ising
{
private:
	// storage of spin coordination
	// true means spin-up, false means spin-down
	std::array<bool, isingConstant::latticeSize> m_spins{};
		
public:
	Ising();

	void initializeSpin();

	void flip(size_t index);
	bool getValue(size_t index) const;
};