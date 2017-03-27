#include "Guesser.h"



Guesser::Guesser()
{
}

Guesser::Guesser(int min, int max)
{
	setRange(min, max);
}


Guesser::~Guesser()
{
}

void Guesser::setRange(int min, int max)
{
	if (min > max) {
		// HACK maybe this should silently swap the values?
		throw std::invalid_argument("min value cannot be greater than max value");
	}
	else {
		m_min = min;
		m_max = max;
	}
}

int Guesser::getGuess()
{
	int guess = (m_min + m_max) / 2;
	return guess;
}

void Guesser::refineRange(int guess, char response)
{
	switch (response) {
	case LOWER:
		m_max = guess - 1;
		if (m_max < m_min) {		//HACK research if there's a better way to keep range valid
			m_max = m_min;
		}
		break;
	case HIGHER:
		m_min = guess + 1;
		if (m_min > m_max) {
			m_min = m_max;
		}
		break;
	default:
		throw std::invalid_argument("Invalid response code passed to Guesser::refineRange()");
	}
}

bool Guesser::isLastGuess()
{
	return m_min == m_max;
}
