/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "Main.h"
#include "FBullCowGame.h"

// make syntax unreal friendly
using FText = std::string;
using int32 = int32;

FBullCowGame BCGame;

int main(int32 argv, int32 args[])
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?";
	std::cout << std::endl << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) //TODO (dane) change the for to while once validating tries
	{
		FText Guess = GetGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();
	return;
}

FText GetGuess() // TODO: change to get valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with only lowercase letters.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;


}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won in " << BCGame.GetCurrentTry() - 1 << " tries!" << std::endl;
		return;
	}
	else
	{
		std::cout << "Oooh. Too bad. You didn't make it." << std::endl;
		return;
	}
}

