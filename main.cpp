#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


//To Make Syntax Unreal Friendly
using FText = std::string;
using int32 = int;

//Function Prototypes as Outside a Class
void PrintIntro();
void PlayGame();
FText GetAValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void PrintWinMessage();
FBullCowGame BCGame; //instantiate a new game

int main()
{
	do
	{	PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}


//Introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}



//Play the game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//	std::cout << MaxTries << std::endl;

	//Loop for the number of turns asking for guesses while game is
	// NOT won and there are still tries remaining
while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= BCGame.GetMaxTries()) 
	{
		FText Guess = GetAValidGuess(); 

		//Submits Valid Guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//Gives Feedback
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
	return;
}



//Loop continually until valid guess is obtained
FText GetAValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 Tries = BCGame.GetCurrentTries();
		std::cout << "\nTry " << Tries << " of " << BCGame.GetMaxTries() << "." << std::endl;
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram as your guess:\n";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please Enter a Word Without Repeating Letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " Letter Isogram.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default://Assume Guess is Valid
			break;
		}
	} while (Status != EGuessStatus::Ok);
	return(Guess);
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return(Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		PrintWinMessage();
	}
	else
	{
		std::cout << "\nYou have run out of tries, better luck next time\n";
	}
}
void PrintWinMessage()
{
	std::cout << "\n                                       /\;    \;\\\n";
	std::cout << "                                   __  \\\\____//\n";
	std::cout << "                                  \___   (o)  (o  }\n";
	std::cout << "       _____________________________/          :--'   CONGRATULATIONS\n";
	std::cout << "   ,-,'`@@@@@@@@       @@@@@@         \\_    `__\\\n";
	std::cout << "  \;:(  @@@@@@@@@        @@@             \\___(o'o)\n";
	std::cout << "  :: )  @@@@          @@@@@@        ,'@@(  `===='        YOU\n";
	std::cout << "  :: : @@@@@:          @@@@         `@@@:\n";
	std::cout << "  :: \\  @@@@@:       @@@@@@@)    (  '@@@'\n";
	std::cout << "  \;\; /\\      /`,    @@@@@@@@@\\   :@@@@@)                   HAVE\n";
	std::cout << "  ::/  )    {_----------------:  :~`,~~\;\n";
	std::cout << " \;\;'`\; :   )                  :  / `\; \;\n";
	std::cout << "\;\;\;\; : :   ;                  :  \;  \; :                        WON !!!\n";
	std::cout << "`'`' / :  :                   :  :  : :\n";
	std::cout << "    )_ \\__;      ";"          :_ \;  \\_\\       `,','\n";
	std::cout << "    :__\\  \\    * `,'*         \\  \\  :  \\   *  8`\;'*  *\n";
	std::cout << "        `^'     \\ :/           `^'  `-^-'   \\v/ :  \\/   -Bill Ames-";
	std::cout << "\n\nYou have sucessfully guessed the hidden word.\n";
	return;
}