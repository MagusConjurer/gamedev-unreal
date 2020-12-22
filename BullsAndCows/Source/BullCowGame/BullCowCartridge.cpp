// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

    PrintLine(TEXT("Valid words: %i"), GetValidWords(Words).Num());
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
    HiddenWord = TEXT("horde");
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
    PrintLine(TEXT("\nPress Enter to play again."));
}

bool UBullCowCartridge::IsIsogram(const FString Word) const
{
    for (int32 i = 0; i < Word.Len() - 1; i++) {
        for (int32 j = i + 1; j < Word.Len(); j++) {
            if (Word[i] == Word[j]) {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    // Check array for valid isograms of length 4-8 characters
    // Using a range based for loop to go through the entire collection of words
    for (FString Word : WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    // Check for the correct word
    if (Guess == HiddenWord) {
        ClearScreen();
        PrintLine(TEXT("That is the correct word!"));
        EndGame();
        return;
    } 

    PrintLine(TEXT("You have not entered the correct word."));
    --Lives;

    // Check if the player has lives remaining
    if (Lives == 0) {
        ClearScreen();
        PrintLine(TEXT("You have run out of lives."));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    } 

    // Check for the correct length
    if (HiddenWord.Len() != Guess.Len()) {
        PrintLine(TEXT("Your answer was %i letters instead of %i."), Guess.Len(), HiddenWord.Len());
    }

    // Check for an isogram
    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("The hidden word has no repeating letters."));
    }

    PrintLine(TEXT("You have %i lives remaining."), Lives); 
    PrintLine(TEXT("Enter another word."));
}
