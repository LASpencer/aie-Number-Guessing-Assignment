#pragma once

// Possible responses for controlling refineRange
enum ResponseCode {
	HIGHER,
	LOWER,
	CORRECT,
	INVALID_INPUT
};

/*
Guesser Class

Using binary search algorithm, guesses the user's number based on range given
*/
class Guesser
{
public:
	Guesser();
	Guesser(int min, int max);
	~Guesser();

	/* Sets minimum and maximum possible values to guess
		Throws exeption if min > max

		min = minimum value
		max = maximum value
	*/
	void setRange(int min, int max);

	/* Calculates guess as midpoint between m_min and m_max
	*/
	void calculateGuess();

	/*	Returns current guess
	*/
	int getGuess();

	/* Updates minimum and maximum possible values based on user respone
		response = response code, HIGHER means number is higher than guess, LOWER means number is lower than guess
	*/
	void refineRange(ResponseCode response);

	// Returns true if m_min == m_max, so only one value is possible
	bool isLastGuess();

	const int MIN = 0x80000000;
	const int MAX = 0x7FFFFFFF;

private:
	int m_min;
	int m_max;
	int m_guess;
};

