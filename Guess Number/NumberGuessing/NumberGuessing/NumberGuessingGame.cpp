#include "libraries.h"
#include "Guesser.h"

const int MIN = 0;
const int MAX = 10000;
char parseResponse(std::string response); //HACK

std::map<std::string, char> inputToResponseCode = {
	{"lower",Guesser::LOWER},
	{ "too high",Guesser::LOWER },
	{"l",Guesser::LOWER},
	{ "higher",Guesser::HIGHER },
	{ "too low",Guesser::HIGHER },
	{"h",Guesser::HIGHER},
	{"correct",Guesser::CORRECT},
	{"right",Guesser::CORRECT},
	{"yes",Guesser::CORRECT},
	{"y",Guesser::CORRECT}
};

int main() {
	Guesser guesser = Guesser();
	guesser.setRange(MIN, MAX);
	// TODO let the user set the range
	int guess;
	std::string response;
	char responseCode;
	bool hasWon = false;

	std::cout << "Think of a number between " << MIN << " and " << MAX<<std::endl;
	do {
		guess = guesser.getGuess();
		std::cout << "Is it " << guess << "?\n";
		std::getline(std::cin,response);
		responseCode = parseResponse(response);
		switch (responseCode) {
		case Guesser::HIGHER:
		case Guesser::LOWER:
			guesser.refineRange(guess, responseCode);
			break;
		case Guesser::CORRECT:
			std::cout << "Yes! I got it!\n";
			hasWon = true;
			break;
		default:
			std::cout << "Sorry, I didn't understand you\n";
		}
		if (guesser.isLastGuess()) {			//HACK
			std::cout << "Then it must be " << guesser.getGuess() << std::endl;
			hasWon = true;
		}
	} while (!hasWon);		//HACK explicitly make it about winning
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