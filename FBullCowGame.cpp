#pragma once
#include "FBullCowGame.h"
#include <map>

//To Make Syntax Unreal Friendly
#define TMap std::map  
using int32 = int;

FBullCowGame::FBullCowGame() {	Reset(); }

int32 FBullCowGame::GetCurrentTries() const {	return MyCurrentTries; }
int32 FBullCowGame::GetHiddenWordLength() const {	return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}


bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat zero and one letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]==true) { return false; }//not an isogram
		else { LetterSeen[Letter] = true; }
	}
	return true;//for example if /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (islower(Letter) == false) { return false; }
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	//If Guess isn't an isogram return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	//If Guess isn't all lowercased return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())	//If Guess length is wrong return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::Ok;
	}


	//otherwise return ok
}


//receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTries++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //Assume Same Length as Guess
	//loop through all letters in the hidden word
	for (int32 i = 0;i <WordLength ;i++)
	{//loop through all letters in the guess
		for (int32 j = 0;j < WordLength;j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		//compare letters against the hidden word
	if (BullCowCount.Bulls == WordLength) 
	{
		bIsGameWon = true; 
	}
	else
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "jolt";
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	MyCurrentTries = 1;
	return;
}

