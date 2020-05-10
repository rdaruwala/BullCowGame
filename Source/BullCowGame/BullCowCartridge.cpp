// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    PrintLine(TEXT("Welcome to the Bull Cows Game"));
    PrintLine(TEXT("Guess the four-letter word..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Check if isogram
    // Check if number of letters match
    // If not, reprompt for new guess
    
    if(HiddenWord.Equals(Input, ESearchCase::IgnoreCase)){
        PrintLine(TEXT("You win!"));
    }
    else{
        PrintLine(TEXT("You lose!"));

        // Decrement lives
        // If lives == 0, gameover, prompt to restart
        // Else loop back up for next guess
    }
}

void UBullCowCartridge::SetupGame(){
    HiddenWord = TEXT("make");
    lives = 3;
}