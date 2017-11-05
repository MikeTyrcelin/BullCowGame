/* The game is a simple word logic puzzle.  Simply guess the word in
the allotted number of tries given.
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//All Values Initialised to Zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();  //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO make a richer return value
	

	//counts # of Bulls and increases # of tries, assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

//Please Try to Ignore This and Focus Above ^^
private:
	//See Constructor for Initialization
	int32 MyCurrentTries;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};