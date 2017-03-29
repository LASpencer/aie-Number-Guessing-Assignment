#include <iostream>
#include <map>
#include <string>
#include <exception>
#include "Guesser.h"

// Gets integer from input stream, making sure it's valid
int InputRangeLimit();
// Returns response code mapped to by user input
ResponseCode ParseResponse(std::string response);

// Map of understood inputs to their meaning
std::map<std::string, ResponseCode> inputToResponseCode = {
	{"lower",LOWER},
	{ "too high",LOWER },
	{"l",LOWER},
	{ "higher",HIGHER },
	{ "too low",HIGHER },
	{"h",HIGHER},
	{"yes",CORRECT},
	{"y",CORRECT}
};

int main() {
	Guesser guesser = Guesser();
	int max;
	int min;
	std::string response;			//Text input by user
	ResponseCode responseCode;		//Meaning of user input
	//User inputs max and min values
	std::cout << "Enter the lowest number" << std::endl;
	min = InputRangeLimit();
	std::cout << "Enter the highest number" << std::endl;
	max = InputRangeLimit();
	while (min >= max) {
		if(min == max){
			// Prompt user to input two different numbers
			std::cout << "A number between " << min << " and " << max << " isn't exactly a challenge." << std::endl;
		}
		else {
			// Check if the user wrote the wrong numbers, or just input them in the wrong order
			std::cout << "You might have that backwards. Did you mean a number between " << max << " and " << min << "?" << std::endl;
			std::getline(std::cin, response);
			if (ParseResponse(response) == CORRECT) {
				// Swap max and min
				int temp = max;
				max = min;
				min = temp;
				// Break from loop as max > min
				break;
			}
		}
		std::cout << "Enter the lowest number" << std::endl;
		min = InputRangeLimit();
		std::cout << "Enter the highest number" << std::endl;
		max = InputRangeLimit();
	}
	bool playing = true;
	while (playing) {
		bool hasWon = false;
		guesser.SetRange(min, max);
		std::cout << "Think of a number between " << min << " and " << max << std::endl;
		while (!hasWon) {
			// Ask user if current 
			std::cout << "Is it " << guesser.GetGuess() << "?\n";
			std::getline(std::cin, response);
			responseCode = ParseResponse(response);
			switch (responseCode) {
			case HIGHER:
				//TODO if saying higher than max, call user a liar and hasWon = true
				//TODO if higher than m_max, do the same
				guesser.RefineRange(responseCode);
				break;
			case LOWER:
				//TODO if saying lower than min, call user a liar and hasWon = true
				//TODO if lower than m_min, do the same
				guesser.RefineRange(responseCode);
				break;
			case CORRECT:
				// Stop looping through game
				std::cout << "Yes! I got it!\n";
				hasWon = true;
				break;
			case INVALID_INPUT:
			default:
				// If user input can't be matched to a response code
				std::cout << "Sorry, I didn't understand you\n";
			}
			if (guesser.IsLastGuess()) {
				// If only one value is possible, state that value was found instead of prompting user
				std::cout << "Then it must be " << guesser.GetGuess() << std::endl;
				hasWon = true;
			}
		}
		// Ask if player wants to play again
		std::cout << "\nWould you like to play again?" << std::endl;
		std::getline(std::cin, response);
		responseCode = ParseResponse(response);	
		playing = responseCode == CORRECT;
	}
}

int InputRangeLimit()
{
	int limit;
	std::cin >> limit;
	// Check input was an integer
	while (std::cin.fail()) {
		std::cout << "Invalid input. Please enter an integer number." << std::endl;
		// Clear failbit and flush buffer
		std::cin.clear();
		std::cin.ignore(265,'\n');
		std::cin >> limit;
	}
	// Flush cin buffer
	std::cin.ignore(265,'\n');
	return limit;
}

ResponseCode ParseResponse(std::string response){
	//convert response to lower case
	for (size_t i = 0; i < response.length(); i++) {
		response[i] = tolower(response[i]);
	}
	if (inputToResponseCode.count(response) !=0){		// check response exists in map
		return inputToResponseCode[response];
	}
	else {
		return INVALID_INPUT;
	}
}