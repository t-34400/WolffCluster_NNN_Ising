#pragma once
#include "Ising.h"

class Wolff
{
private:
	// spin coordination
	Ising& m_ising;

	// vertical/horizonal parameter divided by Boltzmann constant
	double m_cp_vh{};
	// diagonal parameter divided by Boltzmann constant
	double m_cp_diag{};
	// temperature
	double m_temp{};

	// cluster growth probability in each direction
	double m_growthProbability_vh{};
	double m_growthProbability_diag{};

	// direction of the spin that will be flipped
	bool m_flippedDirection{};

	void growCluster(int time, int space);
	void growInOneDirection(int time, int space, bool isDiagonal);
	bool checkFlipping(bool candidateSitesDirection, bool isDiagonal);

public:
	Wolff(Ising& ising, double cp_vh, double cp_diag = 0.0, double temp = 1.0);

	void setTemperature(double temp);
	void stepForward(int steps=1);
};