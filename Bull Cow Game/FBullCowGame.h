#pragma once
#include <string>

using FText = std::string;
using int32 = int;

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); //TODO(dane) make a better return
	bool CheckGuessValidity(FText guess);
	

private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	bool IsIsogram;

};