#pragma once
#include "libraries.h"
class Guesser
{
public:
	Guesser();
	Guesser(int min, int max);
	~Guesser();
	void setRange(int min, int max);
	int getGuess();
	void refineRange(int guess, char response);
	bool isLastGuess();

	// TODO let player choose a rational number
	static const char HIGHER = 'h';
	static const char LOWER = 'l';
	static const char CORRECT = 'c';
private:
	int m_min;
	int m_max;
};

