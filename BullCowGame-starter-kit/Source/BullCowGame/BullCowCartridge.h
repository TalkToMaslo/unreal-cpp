// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
    void ProcessGuess(const FString& Input);
    void SetGameParams();
    void PrintHiddenWordLength();
    void PrintLives();
    void PlayGame();
    bool IsIsogram(FString Word);
    void CountBullsCows();
    void GameOver();
    void PlayAgain();
    void PrintExitMessage();

	// Your declarations go below!
	private:
    FString HiddenWord;
    int32 Lives;
    int32 Bulls, Cows;
    bool WonGame;
    FString ArrayOfWords[] = {"cake", "egypt", "sword", "lumber", "trouble", "playground", "country", "mango", "siphon", "germanic" , "ambidextrous"};
};
