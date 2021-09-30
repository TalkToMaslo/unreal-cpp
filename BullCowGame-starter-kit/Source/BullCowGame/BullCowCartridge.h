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
    const void PrintWelcomeMessage();
	virtual void BeginPlay() override;
    void loadWords();
	virtual void OnInput(const FString& Input) override;
    void ProcessGuess(const FString& Input);
    void SetGameParams();
    const void PrintHiddenWordLength();
    const void PrintLives();
    void PlayGame();
    const bool IsIsogram(const FString& Word);
    const void CountBullsCows(const FString& Input);
    void GameOver();
    void PlayAgain();
    const void PrintExitMessage();

	// Your declarations go below!
	private:
    bool FirstGame = true;
    FString HiddenWord;
    int32 Lives;
    int32 Bulls, Cows;
    bool WonGame;
    TArray<FString> HiddenWordOptions;
};
