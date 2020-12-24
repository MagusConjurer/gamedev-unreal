// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Get valid words once at the start of the game
    Isograms = GetValidWords(Words);

    InitGame();
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
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    // Set the value, even if it does not hit one of the checks
    FBullCowCount Count;

    // Check if index of Guess matches index of HiddenWord
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]) {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++) {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Check for the correct word
    if (Guess == HiddenWord) {
        ClearScreen();
        PrintLine(TEXT("%s is the correct word!"), *HiddenWord);
        EndGame();
        return;
    } 

    PrintLine(TEXT("\nYou have not entered the correct word."));
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

    // Check for correct letters and index
    if (Guess.Len() == HiddenWord.Len()) {
        FBullCowCount Score = GetBullCows(Guess);
        PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);
    }
    
    PrintLine(TEXT("You have %i lives remaining."), Lives); 
    PrintLine(TEXT("Enter another word.\n"));
}
