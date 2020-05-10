// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine(TEXT("Welcome to the Bull Cows Game"));
    PrintLine(TEXT("Guess the four-letter word..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("make");
    
    if(Input == HiddenWord){
        PrintLine(TEXT("You win!"));
    }
    else{
        PrintLine(TEXT("You lose!"));
    }
}