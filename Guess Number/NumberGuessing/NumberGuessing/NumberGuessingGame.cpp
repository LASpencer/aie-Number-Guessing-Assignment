#include "libraries.h"
#include "Guesser.h"

const int MIN = 0xFFFF0000;
const int MAX = 0x0000FFFF; //HACK for testing

// Returns response code mapped to by user input
char parseResponse(std::string response);

// Map of understood inputs to their meaning
std::map<std::string, char> inputToResponseCode = {
	{"lower",Guesser::LOWER},
	{ "too high",Guesser::LOWER },
	{"l",Guesser::LOWER},
	{ "higher",Guesser::HIGHER },
	{ "too low",Guesser::HIGHER },
	{"h",Guesser::HIGHER},
	{"yes",Guesser::CORRECT},
	{"y",Guesser::CORRECT}
};

int main() {
	Guesser guesser = Guesser();
	int max = MAX;
	int min = MIN;
	// TODO let the user set the range
	std::string response;
	char responseCode;
	bool playing = true;
	while (playing) {
		bool hasWon = false;
		guesser.setRange(min, max);
		std::cout << "Think of a number between " << MIN << " and " << MAX << std::endl;
		do {
			// Ask user if current 
			std::cout << "Is it " << guesser.getGuess() << "?\n";
			std::getline(std::cin, response);
			responseCode = parseResponse(response);
			switch (responseCode) {
			case Guesser::HIGHER:
			case Guesser::LOWER:
				guesser.refineRange(responseCode);
				break;
			case Guesser::CORRECT:
				// Stop looping through game
				std::cout << "Yes! I got it!\n";
				hasWon = true;
				break;
			default:
				// If user input can't be matched to a response code
				std::cout << "Sorry, I didn't understand you\n";
			}
			if (guesser.isLastGuess()) {
				// If only one value is possible, state that value was found instead of prompting user
				std::cout << "Then it must be " << guesser.getGuess() << std::endl;
				hasWon = true;
			}
		} while (!hasWon);
		// Ask if player wants to play again
		std::cout << "\nWould you like to play again?" << std::endl;
		std::getline(std::cin, response);
		responseCode = parseResponse(response);		//HACK parser should have context/map passed to it
		playing = responseCode == Guesser::CORRECT;
	}
		system("pause");
}

char parseResponse(std::string response){
	//convert response to lower case
	for (int i = 0; i < response.length(); i++) {
		response[i] = tolower(response[i]);
	}
	if (inputToResponseCode.count(response) !=0){		// check response exists in map
		return inputToResponseCode[response];
	}
	else {
		return 0;
	}
}