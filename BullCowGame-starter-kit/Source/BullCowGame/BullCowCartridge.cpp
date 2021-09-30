#include "BullCowCartridge.h"

// Start game
void UBullCowCartridge::BeginPlay()
{
    
    if (FirstGame) {
        Super::BeginPlay();
        
        // load in words
        loadWords();
    }
    
    // Set word and lives
    SetGameParams();
    
    // Instructions
    PrintWelcomeMessage();
    PrintLives();
    PrintHiddenWordLength();
    
    // Start playing
}

// After a player guess
void UBullCowCartridge::OnInput(const FString& Input)
{
    
    // During gameplay
    if (Lives > 0 && !WonGame)
    {
        ClearScreen();
        ProcessGuess(Input);
    }
    
    // Outside gameplay
    else
    {
        PlayAgain();
    }
}

void UBullCowCartridge::SetGameParams()
{
    WonGame = false;
    
    // Select hidden word
    do
    {
        HiddenWord = HiddenWordOptions[FMath::RandRange(0, HiddenWordOptions.Num())];
    }
    while(HiddenWord.Len() < 4 || !IsIsogram(HiddenWord));
    
    // Debug line: remove during production
    PrintLine(HiddenWord);
    
    // Set number of lives
    Lives = HiddenWord.Len();
}

const void UBullCowCartridge::PrintWelcomeMessage()
{
    PrintLine(TEXT("Welcome to the bull cow game!"));
}

const void UBullCowCartridge::PrintLives()
{
    PrintLine(FString::Printf(TEXT("+ You have %i lives left."), Lives));
}

const void UBullCowCartridge::PrintHiddenWordLength()
{
    PrintLine(FString::Printf(TEXT("+ Guess the %i letter isogram..."), HiddenWord.Len()));
}

const void UBullCowCartridge::PrintExitMessage()
{
    PrintLine(TEXT("We hope you enjoyed playing the Bull & Cow game! Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Guess is right
    if (Guess == HiddenWord)
    {
        WonGame = true;
        GameOver();
    }
    
    // Guess has incorrect length
    else if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Wrong answer. Your guess is a %i letter isogram. \nThe hidden word is a %i letter isogram."), Guess.Len(), HiddenWord.Len());
    }
    
    // Guess has correct length but is not an isogram
    else if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Wrong answer. Your guess is not an isogram. \nThe hidden word is a %i letter isogram: it has no repeated letters."), HiddenWord.Len());
    }
    
    // Guess is correct length but wrong word
    else
    {
        // lose a life
        --Lives;
        
        // Remaining lives
        if (Lives > 0)
        {
            // count bulls and cows
            CountBullsCows(Guess);
            
            // show lives left
            PrintLives();
        }
        
        else {
            GameOver();
        }
    }
}

const bool UBullCowCartridge::IsIsogram(const FString& Word)
{

    for (int32 LetterPos = 0; LetterPos < Word.Len(); LetterPos++)
    {
        
        for (int32 OtherLetterPos = LetterPos + 1; OtherLetterPos < Word.Len(); OtherLetterPos++)
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

const void UBullCowCartridge::CountBullsCows(const FString& Guess)
{
    // count bulls (same letter at same index) and cows (same letter at different index)
    Bulls = 0, Cows = 0;
    for (int GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        
        // Same letter at same index
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Bulls++;
        }
        
        // Different letter at same index
        else
        {
            // Check rest of HiddenWord for same letter
            for (int HiddenWordIndex = 0; HiddenWordIndex < HiddenWord.Len(); HiddenWordIndex++)
            {
                // Same letter at different index
                if (Guess[GuessIndex] == HiddenWord[HiddenWordIndex])
                {
                    Cows++;
                }
            }
        }
    }
    
    
    // Print result
    PrintLine(FString::Printf(TEXT("You had %i bull(s) and %i cow(s)."), Bulls, Cows));
}

void UBullCowCartridge::GameOver()
{
    
    // Game won
    if (WonGame)
    {
        PrintLine(TEXT("You won the game!"));
    }
    
    // Game lost
    else
    {
        PrintLine(TEXT("You lost the game!"));
    
        PrintLine(FString::Printf(TEXT("The word was: %s"), *HiddenWord));
    }
    
    // Game ended
    PrintExitMessage();
}

void UBullCowCartridge::PlayAgain()
{
    // New game
    ClearScreen();
    FirstGame = false;
    BeginPlay();
}

void UBullCowCartridge::loadWords() {
        
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    
    FFileHelper::LoadFileToStringArray(HiddenWordOptions, *WordListPath);
}
