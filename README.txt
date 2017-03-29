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

The program is divided into the following files

-NumberGuessingGame.cpp
-Guesser.h
-Guesser.cpp

1- NumberGuessingGame.cpp
This file contains the main method of the program and functions to handle user input
It also contains a map of strings to ResponseCodes (an enumerated type defined in 
Guesser.h)
The minumum and maximum values are validated with a while loop, both in the InputRangeLimit
function and when checking the two numbers are different and in the correct order.
As response is already input within a loop, any invalid input is parsed as the INVALID_INPUT
response code, and the user is told they weren't understood so they can try again in the 
next iteration.

The program is essentially a binary search algorithm. Every iteration, the Guesser object is
asked for its current guess, which is midway between the maximum and minimum values. The 
user either provides a HIGHER/LOWER response, which is passed to the Guesser object so it
can update its range, or they provide a CORRECT response, which ends the loop as the program
declares victory. Also, if updating the range leads to the Guesser's m_max and m_min values
being equal, the loop is ended as the correct number must have been guessed.

2- Guesser.h
The Guesser class and ResponseCode enumeration are declared in this header file.
ResponseCode contains HIGHER, LOWER, CORRECT, and INVALID_INPUT. These are the three possible
responses to the program's guess, and a fourth value for any input not mapped to the other
three.

3- Guesser.cpp
This file contains the definitions of the Guesser class's methods.

Guesser has three member variables: m_min, m_max, and m_guess. m_min and m_max define the range
in which the number to be guessed may exist. When a value is assigned to these members through
the SetRange method, or the RefineRange function is passed HIGHER or LOWER, the CalculateGuess
method is called to assign the mean of m_min and m_max to m_guess. This ensures that m_guess is
always the correct value

To avoid integer overflow and underflow problems, CalculateGuess checks if m_max is greater than
half of 0x7FFFFFFF, or m_min is less than half of 0x80000000. If so, the values are cast as 64 bit
integers before calculating their mean, and the result is cast back to a 32 bit integer.