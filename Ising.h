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

	void flip(int time, int space);
	bool getValue(int time, int space) const;

	// manipulate the spin site index
	// avoid the use of modulo(%) for efficiency
	inline static int moveForwardInTime(int time)
	{
		++time;
		if (time >= isingConstant::timeSize)
			time = 0;
		return time;
	}
	inline static int moveBackwardInTime(int time)
	{
		--time;
		if (time < 0)
			time = isingConstant::timeSize - 1;
		return time;
	}

	inline static int moveForwardInSpace(int space)
	{
		++space;
		if (space >= isingConstant::spaceSize)
			space = 0;
		return space;
	}
	inline static int moveBackwardInSpace(int space)
	{
		--space;
		if (space < 0)
			space = isingConstant::spaceSize - 1;
		return space;
	}
};