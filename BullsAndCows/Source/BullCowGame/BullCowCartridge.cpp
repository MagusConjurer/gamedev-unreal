// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

    PrintLine(TEXT("The hidden word is: "), *HiddenWord); // Show the word for testing
    
    PrintLine(TEXT("Welcome to the Bulls and Cows farm."));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Press Tab, type your guess and then press Enter to begin..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (Input == HiddenWord) {
        PrintLine(TEXT("That is the correct word!"));
    } else {
        PrintLine(TEXT("You have entered the incorrect word."));
        --Lives;
        if(Lives == 0) {
            PrintLine(TEXT("You have run out of lives."));
            PrintLine(HiddenWord);
            // Prompt to play again
        } else {
            // Check if the input is an isogram
            // Check if the input is the correct length
            if(HiddenWord.Len() != Input.Len()) {
                PrintLine(TEXT("NOTE: Your answer was %i letters, instead of %i."), Input.Len(), HiddenWord.Len());
            }
            // Show the new number of Lives
            PrintLine(TEXT("You have %i lives remaining."), Lives); 
            // Prompt to enter another word
        }
    }
}

void UBullCowCartridge::InitGame() // Set the starting values to member variables
{
    HiddenWord = TEXT("Horde");
    Lives = 5;
}