#include <exception>
#include <string>
#include "Guesser.h"

const int MIN = 0x80000000;	//Default value for m_min
const int MAX = 0x7FFFFFFF;	//Default value for m_max

Guesser::Guesser()
{
	SetRange(MIN, MAX);
}

Guesser::Guesser(int min, int max)
{
	SetRange(min, max);
}


Guesser::~Guesser()
{
}

void Guesser::SetRange(int min, int max)
{
	if (min > max) {
		throw std::invalid_argument("min value cannot be greater than max value");
	}
	else {
		m_min = min;
		m_max = max;
		// Calculate new best guess
		CalculateGuess();
	}
}

void Guesser::CalculateGuess()
{
	int guess;
	// Check if int overflow is possible
	if (m_max > 1073741823 || m_min < -1073741824) {
		// Calculate average with 64 bit integer
		signed long long int wideGuess = ((signed long long int)m_max + (signed long long int)m_min) / 2;
		guess = (int)wideGuess;
	}
	else {
		guess = (m_min + m_max) / 2;
	}
	m_guess = guess;
}

int Guesser::GetGuess()
{	
	return m_guess;
}

void Guesser::RefineRange(ResponseCode response)
{
	switch (response) {
	case LOWER:
		// Value is lower than current guess
		m_max = m_guess - 1;
		if (m_max < m_min) {
			m_max = m_min;
		}
		break;
	case HIGHER:
		// Value is higher than current guess
		m_min = m_guess + 1;
		if (m_min > m_max) {
			m_min = m_max;
		}
		break;
	case CORRECT:
		// Guess is correct value
		m_min = m_guess;
		m_max = m_guess;
		break;
	case INVALID_INPUT:
		// Do nothing
		break;
	}
	// Calculate new best guess 
	CalculateGuess();
}

bool Guesser::IsLastGuess()
{
	return m_min == m_max;
}
