#pragma once

// Possible responses for controlling RefineRange
enum ResponseCode {
	HIGHER,				//Number is higher than current guess
	LOWER,				//Number is lower than current guess
	CORRECT,			//Number is equal to guess, or user otherwise indicating agreement
	INVALID_INPUT		//User input could not be understood
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
	void SetRange(int min, int max);

	/* Calculates guess as midpoint between m_min and m_max
	*/
	void CalculateGuess();

	/*	Returns current guess
	*/
	int GetGuess();

	/* Updates minimum and maximum possible values based on user respone
		response = response code, HIGHER means number is higher than guess, LOWER means number is lower than guess
	*/
	void RefineRange(ResponseCode response);

	// Returns true if m_min == m_max, so only one value is possible
	bool IsLastGuess();

private:
	int m_min;		//Minimum possible value of number
	int m_max;		//Maximum possible value of number
	int m_guess;	//Current guess of number
};

