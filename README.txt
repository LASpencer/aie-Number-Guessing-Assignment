NumberGuessing by L. Andrew Spencer 2017

This program asks the user for a minimum and maximum value, and tries to 
guess the number they're thinking of between those values

I. Use
-------

The program will ask for a minimum value and a maximum value, then prompt
the user to think of a number between these values.
The program displays its guess, and the user enters their response.

VALID RESPONSES:

"l", "lower", and "too high" 	: The number is lower than the guess
"h", "higher", and "too low" 	: The number is higher than the guess
"y", "yes"			: The guess is correct.
Anything else			: Program prompts user to re-enter response

All responses are case insensitive.

The program will continue to make guesses until the user says it's correct,
or only one number is possible. It will then ask the user if they want to
play again, using the same range.



II. Design
----------

The program is divided into the following source files

-NumberGuessingGame.cpp
-Guesser.cpp

1- NumberGuessingGame.cpp
This file contains the main method of the program and functions to handle user input
