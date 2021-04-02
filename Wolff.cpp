#include "isingConstant.h"
#include "mersenne.h"
#include "Wolff.h"
#include <cassert>
#include <cmath>

Wolff::Wolff(Ising& ising, double cp_vh, double cp_diag, double temp)
	:m_ising{ ising }, m_cp_vh{ cp_vh }, m_cp_diag{ cp_diag }
{
	setTemperature(temp);
}

void Wolff::setTemperature(double temp)
{
	assert(temp > 0);
	m_temp = temp;
	m_growthProbability_vh = 1 - std::exp(-2.0 * m_cp_vh / temp);
	m_growthProbability_vh = 1 - std::exp(-2.0 * m_cp_diag / temp);
}

void Wolff::stepForward(int steps)
{
	int index{};
	int time{};
	int space{};
	// perform flips as many as sites per step for ergodicity.
	const int totalCount{ steps * isingConstant::latticeSize };

	for (int count{ 0 };count<totalCount;++count)
	{
		// select initial site
		// use modulo to reduce the number of random number generation 
		index = mersenne::getRandomInt(0, isingConstant::latticeSize - 1);
		time = index / isingConstant::spaceSize;
		space = index % isingConstant::spaceSize;

		m_flippedDirection = m_ising.getValue(time, space);
		growCluster(time, space);
	}
}

void Wolff::growCluster(int time, int space)
{
	m_ising.flip(time, space);

	int timeForward{ Ising::moveForwardInTime(time) };
	int timeBackward{ Ising::moveBackwardInTime(time) };
	int spaceForward{ Ising::moveForwardInSpace(space) };
	int spaceBackward{ Ising::moveBackwardInSpace(space) };

	// grow cluster vertical/horizonal direction
	growInOneDirection(time, spaceForward, false);
	growInOneDirection(time, spaceBackward, false);
	growInOneDirection(timeForward, space, false);
	growInOneDirection(timeBackward, space, false);

	// grow cluster diagonal direction
	growInOneDirection(timeForward, spaceForward, true);
	growInOneDirection(timeForward, spaceBackward, true);
	growInOneDirection(timeBackward, spaceForward, true);
	growInOneDirection(timeBackward, spaceBackward, true);
}

void Wolff::growInOneDirection(int time, int space, bool isDiagonal)
{
	if (checkFlipping(m_ising.getValue(time, space), isDiagonal))
		growCluster(time, space);
}

bool Wolff::checkFlipping(bool candidateSitesDirection, bool isDiagonal)
{
	// the flipped site must be in the same direction of the original site
	if (!(candidateSitesDirection ^ m_flippedDirection))
	{
		if (isDiagonal)
		{
			return (mersenne::getProbability() < m_growthProbability_diag);
		}
		else
		{
			return (mersenne::getProbability() < m_growthProbability_vh);
		}
	}
	return false;
}