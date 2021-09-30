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
    void PrintWelcomeMessage() const;
	virtual void BeginPlay() override;
    void loadWords();
	virtual void OnInput(const FString& Input) override;
    void ProcessGuess(const FString& Input);
    void SetGameParams();
    void PrintHiddenWordLength() const;
    void PrintLives() const;
    void PlayGame();
    bool IsIsogram(const FString& Word) const;
    void CountBullsCows(const FString& Input) const;
    void GameOver();
    void PlayAgain();
    void PrintExitMessage() const;

	// Your declarations go below!
	private:
    bool FirstGame = true;
    FString HiddenWord;
    int32 Lives;
    bool WonGame;
    TArray<FString> HiddenWordOptions;
};
