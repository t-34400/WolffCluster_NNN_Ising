#include "isingConstant.h"
#include "mersenne.h"
#include "Wolff.h"
#include <cassert>
#include <cmath>

Wolff::Wolff(double cp_vh, double cp_diag, double temp)
	:m_cp_vh{ cp_vh }, m_cp_diag{ cp_diag }
{
	setTemperature(temp);
}

void Wolff::initialize()
{
	m_ising.initializeSpin();
}

void Wolff::setTemperature(double temp)
{
	assert(temp > 0);
	m_temp = temp;
	m_growthProbability_vh = 1 - std::exp(-2.0 * m_cp_vh / temp);
	m_growthProbability_diag = 1 - std::exp(-2.0 * m_cp_diag / temp);
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

double Wolff::getMagnetization() const
{
	int magnetization{ 0 };
	for (auto spin : m_ising.getIsingArray())
	{
		magnetization += spin ? 1 : -1;
	}
	return static_cast<double>(magnetization) / isingConstant::latticeSize;
}

double Wolff::getEnergy() const
{
	// energy of vertical/horizonal interaction
	int energy_vh{ 0 };
	// diagonal interaction
	int energy_diag{ 0 };

	// temporary variable
	int timeForward{};
	int timeBackward{};
	int spaceForward{};
	bool originalDirection;
	int space{};

	for (int time{ 0 };time<isingConstant::timeSize;++time)
	{ 
		for (space = 0; space < isingConstant::spaceSize; ++space)
		{
			timeForward = Ising::moveForwardInTime(time);
			timeBackward = Ising::moveBackwardInTime(time);
			spaceForward = Ising::moveForwardInSpace(space);
			originalDirection = m_ising.getValue(time, space);

			energy_vh += (originalDirection ^ m_ising.getValue(timeForward, space)) ? -1 : 1;
			energy_vh += (originalDirection ^ m_ising.getValue(time, spaceForward)) ? -1 : 1;
			energy_diag += (originalDirection ^ m_ising.getValue(timeForward, spaceForward)) ? -1 : 1;
			energy_diag += (originalDirection ^ m_ising.getValue(timeBackward, spaceForward)) ? -1 : 1;
		}
	}

	return (m_cp_vh * energy_vh + m_cp_diag * energy_diag) / isingConstant::latticeSize;
}
double Wolff::getCorrelationInTime(int distance) const
{
	assert(distance <= isingConstant::timeSize / 2);

	int correlation{ 0 };

	// spatial coordinate of one site
	int space1{};
	// spin direction of one site
	bool spin1{};
	// spatial coordinate of another site
	int space2{};
	// time coordinate of another site
	int time2{ distance };

	for (int time1{ 0 }; time1 < isingConstant::timeSize; ++time1)
	{
		// sum in spatial direction to get zero-momentum
		for (space1 = 0; space1 < isingConstant::spaceSize; ++space1)
		{
			spin1 = m_ising.getValue(time1, space1);
			for (space2 = 0; space2 < isingConstant::spaceSize; ++space2)
			{
				correlation += (spin1 ^ m_ising.getValue(time2, space2)) ? -1 : 1;
			}
		}
		time2 = Ising::moveForwardInTime(time2);
	}

	return static_cast<double>(correlation) / (isingConstant::latticeSize * isingConstant::spaceSize);
}