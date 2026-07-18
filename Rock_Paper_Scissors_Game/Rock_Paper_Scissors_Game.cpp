#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

//====================
// Enums
//====================

enum enGameChoices
{
    rock = 1,
    paper = 2,
    Scissors = 3
};

enum enWinner
{
    Player = 1,
    Computer = 2,
    NoWinner = 3
};
//====================
// Structs
//====================

struct stGameRound
{
    short RoundNum = 0;
    enGameChoices PlayerChoice;
    enGameChoices ComputerChoice;
    enWinner RoundWinner;
    string RoundWinnerName = "";
};

struct stGameResults
{
    short TotalRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short Draws = 0;
    enWinner GameWinner;
    string GameWinnerName = "";
};
//====================
// Function Prototypes
//====================

int RandNum(int from, int to);
short GetGameRounds();
enGameChoices GetPlayerChoice();
enGameChoices GetComputerChoice();
enWinner WinnerOfRound(stGameRound GameRound);
void PrintRoundResults(stGameRound GameRound);
void StartGame();
string Tabs(int NumsOfTabs);
string WinnerName(enWinner Winner);
string ChoiceName(enGameChoices Choice);
enWinner DetermineGameWinner(short, short, short);
void ResetScreen();
void PrintGameOverScreen();
void PrintFinalGameResults(stGameResults);
stGameResults PlayRound(short);
void SetWinnerScreenColour(enWinner);

//====================
// Utility Functions
//====================
int RandNum(int from, int to)
{
    int RandNum = rand() % (to - from + 1) + from;
    return RandNum;
} 

string Tabs(int NumsOfTabs)
{
    string t = "";
    for (int i = 0; i < NumsOfTabs; i++)
    {
        t += "\t";
    }
    return t;
} 
void ResetScreen ()
{
    system("cls");
    system ("color 0F"); //Black
}
//====================
// Input Functions
//====================
enGameChoices GetPlayerChoice()
{
    int PChoice;
    do
    {
        cout << "Choose from [1]:Rock [2]:Paper [3]:Scissors \n";
        cin >> PChoice;
    } while ((PChoice < 1) || (PChoice > 3));

    return (enGameChoices)PChoice;
}
short GetGameRounds ()
{ short Rounds = 0 ;
  do {
   cout<<"How Many Rounds you want to play 1:10\n";
   cin >>Rounds;
  }while ((Rounds < 1 ) || (Rounds > 10)); 
  return Rounds;
}

//====================
// Game Logic
//====================
enGameChoices GetComputerChoice()
{
    return (enGameChoices)RandNum(1, 3);
}


enWinner WinnerOfRound(stGameRound GameRound) 
{ 
    if (GameRound.PlayerChoice == GameRound.ComputerChoice)
    {
        return enWinner::NoWinner;
    }
    switch (GameRound.PlayerChoice)
    {
    case enGameChoices::rock:
        if (GameRound.ComputerChoice == enGameChoices::paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoices::paper:
    if (GameRound.ComputerChoice == enGameChoices::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoices::Scissors:
        if (GameRound.ComputerChoice == enGameChoices::rock)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}
enWinner DetermineGameWinner (short PlayerWins, short ComputerWins, short Draws)
{
    if (PlayerWins > ComputerWins)
    return enWinner::Player;
    else if (PlayerWins < ComputerWins)
    return enWinner::Computer;
    else 
    return enWinner::NoWinner;
}

stGameResults PlayRound (short Rounds)
{
     stGameRound GameRound;
    short ComputerWins = 0 , PlayerWins = 0 , Draws = 0;
    for (int RoundNum = 1 ; RoundNum <= Rounds ; RoundNum++ )
    {
        cout << Tabs(1) << "Round [" << RoundNum << "] begins:" << endl;
     GameRound.RoundNum = RoundNum;
     GameRound.ComputerChoice = GetComputerChoice();
     GameRound.PlayerChoice = GetPlayerChoice();
     GameRound.RoundWinner = WinnerOfRound(GameRound);
     GameRound.RoundWinnerName = WinnerName(GameRound.RoundWinner);

     if (GameRound.RoundWinner == enWinner::Player)
        ++PlayerWins;
     else if (GameRound.RoundWinner == enWinner::Computer)
        ++ComputerWins;
     else 
        ++Draws;
    
    PrintRoundResults(GameRound);
    } 
   return { Rounds ,PlayerWins, ComputerWins, Draws, 
   DetermineGameWinner(PlayerWins, ComputerWins , Draws),
   WinnerName(DetermineGameWinner(PlayerWins, ComputerWins , Draws))};
}
//====================
// Output Functions
//====================
string WinnerName(enWinner Winner)
{
    string ArrWinner[3] = {"Player", "Computer", "NoWinner"};
    return ArrWinner[Winner - 1];
}

string ChoiceName(enGameChoices Choice)
{
    string ArrChoice[3] = {"Rock", "Paper", "Scissors"};
    return ArrChoice[Choice - 1];
}
void SetWinnerScreenColour(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F"); // Green
        break;

    case enWinner::Computer:
        system("color 4F"); // Red
        cout << "\a";
        break;

    default:
        system("color 6F"); // Yellow
        break;
    }
}
void PrintRoundResults (stGameRound GameRound)
{
    SetWinnerScreenColour(GameRound.RoundWinner);
    cout << "__________________Round [" << GameRound.RoundNum << "]____________________\n";
    cout << "Player Choice  : " << ChoiceName(GameRound.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(GameRound.ComputerChoice) << endl;
    cout << "Round Winner   : " << GameRound.RoundWinnerName << endl;
    cout << "_______________________________________________________\n";
}
void PrintGameOverScreen()
{
    cout << Tabs(2) << "_______________________________________________________________\n\n";
    cout << Tabs(2) << "              +++ G A M E  O V E R +++\n";
    cout << Tabs(2) << "_______________________________________________________________\n\n";
}

void PrintFinalGameResults(stGameResults GameResults)
{
    SetWinnerScreenColour(GameResults.GameWinner);

    cout << Tabs(2) << " ____________________________[Game Results]____________________ \n";
    cout << Tabs(2) << " Game rounds        :" << GameResults.TotalRounds << endl;
    cout << Tabs(2) << " Player won times   :" << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << " Computer won times :" << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << " Draw times         :" << GameResults.Draws << endl;
    cout << Tabs(2) << " Final Winner       :" << GameResults.GameWinnerName << endl;
    cout << Tabs(2) << " ______________________________________________________________\n";
}

//====================
// Main Game
//====================
 void StartGame()
 { char PlayAgain;
    do{
    ResetScreen();
    stGameResults GameResults = PlayRound (GetGameRounds());
    PrintGameOverScreen();
    PrintFinalGameResults(GameResults);
    
    cout << endl << Tabs(3) << "Do you want to play again ? Y/N ";
    cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
 }
 
int main ()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}

