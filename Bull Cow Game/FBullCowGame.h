#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); //TODO(dane) make a better return
	bool CheckGuessValidity(FString);
	FBullCowCount SubmitGuess(FString);
	

private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries; 
	FString MyHiddenWord;
	bool IsIsogram;

};