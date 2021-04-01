#include "Ising.h"

Ising::Ising()
{
	initializeSpin();
}

void Ising::initializeSpin()
{
	for (auto& spin : m_spins)
		spin = mersenne::getTF();
}

void Ising::flip(size_t index)
{
	m_spins.at(index) = !m_spins.at(index);
}

bool Ising::getValue(size_t index) const
{
	return m_spins.at(index);
}