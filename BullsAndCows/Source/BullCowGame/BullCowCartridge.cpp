// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Showing the word for testing
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // Check whether the game is still in play
    if (bGameOver) { 
        ClearScreen();
        InitGame();
    } else { // Check PlayerGuess
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame() // Set the starting values to member variables
{
    HiddenWord = TEXT("Horde");
    Lives = 5;
    bGameOver = false;

    PrintLine(TEXT("Welcome to the Bulls and Cows farm."));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Press Tab, type your guess and then press Enter to begin..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    if (Guess == HiddenWord) {
        PrintLine(TEXT("That is the correct word!"));
        EndGame();
    } else {
        PrintLine(TEXT("You have entered the incorrect word."));
        --Lives;
        if (Lives == 0) {
            PrintLine(TEXT("You have run out of lives."));
            PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
            EndGame();
        } else {
            // Check if the guess is an isogram
            // Check if the guess is the correct length
            if(HiddenWord.Len() != Guess.Len()) {
                PrintLine(TEXT("NOTE: Your answer was %i letters \ninstead of %i."), Guess.Len(), HiddenWord.Len());
            }
            PrintLine(TEXT("You have %i lives remaining."), Lives); 
            PrintLine(TEXT("Enter another word."));
        }
    }
}