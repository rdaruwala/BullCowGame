// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("Guess the %i letter word..."), HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver){
        ClearScreen();
        SetupGame();
    }
    else{
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame(){

    GetValidWords(&words);

    HiddenWord = words[FMath::RandRange(0, words.Num()-1)];
    bGameOver = false;
    lives = HiddenWord.Len();

    PrintLine(FString::Printf(TEXT("Your hidden word is: %s"), *HiddenWord)); //Debug Line

    PrintLine(TEXT("Welcome to the Bull Cows Game"));
    PrintLine(TEXT("You have: %i lives"), lives);
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again..."));

}

void UBullCowCartridge::ProcessGuess(const FString &Guess){
        if(HiddenWord.Equals(Guess, ESearchCase::IgnoreCase)){
            PrintLine(TEXT("You win!"));
            EndGame();
            return;
        }

        if(HiddenWord.Len() != Guess.Len()){
            PrintLine(FString::Printf(TEXT("Incorrect number of letters: %i required,\nYou input: %i"), HiddenWord.Len(), Guess.Len()));
            return;
        }

        if(!IsIsogram(Guess)){
            PrintLine(TEXT("Word must be an isogram!\nTry again..."));
            return;
        }

        if(--lives == 0){
            ClearScreen();
            PrintLine(TEXT("Game over! The word was: %s"), *HiddenWord);
            EndGame();
            return;
        }

        FBullCowCount count = GetBullCows(Guess);

        PrintLine(TEXT("Bulls: %i, Cows: %i\nLives remaining: %i"), count.Bulls, count.Cows, lives);
}

bool UBullCowCartridge::IsIsogram(const FString &word) const{
    for(int32 i = 0; i < word.Len(); i++){
        for(int32 j = i+1; j < word.Len(); j++){
            if(word[i] == word[j]){
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::GetValidWords(TArray<FString> *words){
    for(int32 i = 0; i < words->Num(); i++){
        if(!IsIsogram((*words)[i])){
            words->RemoveAt(i--);
        }
    }
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &word) const{
    FBullCowCount toReturn;

    for(int i = 0; i < word.Len(); i++){
        for(int j = 0; j < HiddenWord.Len(); j++){
            if(word[i] == HiddenWord[j]){
                if(i == j){
                    toReturn.Bulls++;
                }
                else{
                    toReturn.Cows++;
                }
                break;
            }
        }
    }

    return toReturn;
}