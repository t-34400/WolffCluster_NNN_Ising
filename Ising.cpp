#include "Ising.h"
#include "mersenne.h"

Ising::Ising()
{
	initializeSpin();
}

void Ising::initializeSpin()
{
	for (auto& spin : m_spins)
		spin = mersenne::getRandomBool();
}

void Ising::flip(int time, int space)
{
	int index{ time * isingConstant::spaceSize + space };
	m_spins.at(index) = !m_spins.at(index);
}

bool Ising::getValue(int time, int space) const
{
	int index{ time * isingConstant::spaceSize + space };
	return m_spins.at(index);
}

const auto& Ising::getIsingArray() const
{
	return m_spins;
}