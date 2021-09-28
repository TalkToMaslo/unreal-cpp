#include "BullCowCartridge.h"

// Start game
void UBullCowCartridge::BeginPlay()
{
    
    Super::BeginPlay();
    
    // Set word and lives
    SetGameParams();
    
    // Instructions
    PrintWelcomeMessage();
    PrintLives();
    PrintHiddenWordLength();
    
    // Start playing
    PlayGame();
}

// After a player guess
void UBullCowCartridge::OnInput(const FString& Input)
{
    ClearScreen();
        
    ProcessGuess(Input);
}

void UBullCowCartridge::SetGameParams()
{
    srand(TIME(NULL));
    WonGame = false;
    HiddenWord = ArrayOfWords[rand() % 12];
    Lives = HiddenWord.Len();
}

// Controls game duration
void UBullCowCartridge::PlayGame()
{
    while (Lives > 0 && !WonGame)
    {
        FString UserGuess;
        cin >> UserGuess;
        OnInput(UserGuess);
    }
    
    GameOver();
}

void UBullCowCartridge::PrintWelcomeMessage()
{
    PrintLine(TEXT("Welcome to the bull cow game!"));
}

void UBullCowCartridge::PrintLives()
{
    PrintLine(FString::Printf(TEXT("+ You have %i lives"), Lives));
}

void UBullCowCartridge::PrintHiddenWordLength()
{
    PrintLine(FString::Printf(TEXT("+ Guess the %i letter isogram..."), HiddenWord.Len()));
}

void UBullCowCartridge::PrintExitMessage()
{
    PrintLine(TEXT("We hope you enjoyed playing the bull cow game!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Guess is right
    if (Guess == HiddenWord)
    {
        WonGame = true;
    }
    
    // Guess is not an isogram
    else if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Wrong answer. Your guess is not an isogram. \nThe hidden word is a %i letter isogram: it has no repeated letters."), HiddenWord.Len());
    }
    
    // Guess is an isogram but incorrect length
    else if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Wrong answer. Your guess is a %i letter isogram. \nThe hidden word is a %i letter isogram."), Guess.Len(), HiddenWord.Len());
    }
    
    // Guess is correct length but wrong word
    else
    {
        // lose a life
        --Lives;
        
        // Remaining lives
        if (Lives > 0)
        {
            // count bulls/cows
            CountBullsCows();
            
            // show lives left
            PrintLives();
        }
    }
}

bool UBullCowCartridge::IsIsogram(FString Word)
{

    for (int LetterPos = 0; LetterPos < Word.Len(); LetterPos++)
    {
        
        for (int OtherLetterPos = LetterPos + 1; OtherLetterPos < Word.Len(); OtherLetterPos++)
        {
            
            // same letter found twice
            if (Word[LetterPos] == Word[OtherLetterPos])
            {
                // word is not isogram
                return false;
            }
        }
    }
    
    // no repeated letters, word is isogram
    return true;
}

void UBullCowCartridge::CountBullsCows()
{
    // count bulls
    Bulls =
    
    // count cows
    Cows =
    
    // Print result
    PrintLine(FString::Printf(TEXT("You had %i bulls and %i cows."), Bulls, Cows));
    
}

void UBullCowCartridge::GameOver()
{
    
    if (WonGame)
    {
        PrintLine(TEXT("You won the game!"));
    }
    
    else
    {
        
        PrintLine(TEXT("You lost the game!"));
    
        PrintLine(FString::Printf(TEXT("The word was: %s"), *HiddenWord));
    }
    
    PlayAgain();
        
}

void UBullCowCartridge::PlayAgain()
{
    PrintLine(TEXT("Do you want to play again?"));
    
    //if yes play again
    if ()
    {
        ClearScreen();
        BeginPlay();
    }
    
    //if no exit
    else
    {
        PrintExitMessage();
    }
}

