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
    Player1 = 1,
    Player2 = 2,
    Computer = 3,
    NoWinner = 4
};

enum enCompetitor
{
    Person = 1,
    PC = 2
};
//====================
// Structs
//====================

struct stGameRound
{
    short RoundNum = 0;
    enGameChoices Player1Choice;
    enGameChoices Player2Choice;
    enGameChoices ComputerChoice;
    enWinner RoundWinner;
    string RoundWinnerName = "";
};

struct stGameResults
{
    short TotalRounds = 0;
    short Player1WinTimes = 0;
    short Player2WinTimes = 0;
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
enWinner CPWinnerOfRound(stGameRound GameRound);
enWinner PPWinnerOfRound(stGameRound GameRound);
void PrintRoundResults(enCompetitor Competitor,stGameRound GameRound);
void StartGame();
string Tabs(int NumsOfTabs);
string WinnerName(enWinner Winner);
string ChoiceName(enGameChoices Choice);
enWinner DetermineGameWinner(short, short, short);
enCompetitor DetermineCompetitor();
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
void ResetScreen()
{
    system("cls");
    system("color 0F"); // Black
}
//====================
// Input Functions
//====================
enGameChoices GetPlayerChoice()
{
    int PChoice;
    do
    {
        cout << "Choose from [1]:Rock [2]:Paper [3]:Scissors ";
        cin >> PChoice;
    } while ((PChoice < 1) || (PChoice > 3));

    return (enGameChoices)PChoice;
}

enCompetitor DetermineCompetitor()
{
    int Competitor;
    do
    {
        cout << "Play Against Player or PC ? [1]:Player [2]:PC ";
        cin >> Competitor;
    } while ((Competitor > 2) || (Competitor < 1));
    return (enCompetitor)Competitor;
}

short GetGameRounds()
{
    short Rounds = 0;
    do
    {
        cout << "How Many Rounds you want to play 1:10  ";
        cin >> Rounds;
    } while ((Rounds < 1) || (Rounds > 10));
    return Rounds;
}

//====================
// Game Logic
//====================
enGameChoices GetComputerChoice()
{
    return (enGameChoices)RandNum(1, 3);
}

enWinner CPWinnerOfRound(stGameRound GameRound)
{
    if (GameRound.Player1Choice == GameRound.ComputerChoice)
    {
        return enWinner::NoWinner;
    }
    switch (GameRound.Player1Choice)
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
    return enWinner::Player1;
}
enWinner PPWinnerOfRound(stGameRound GameRound)
{
    if (GameRound.Player1Choice == GameRound.Player2Choice)
    {
        return enWinner::NoWinner;
    }
    switch (GameRound.Player1Choice)
    {
    case enGameChoices::rock:
        if (GameRound.Player2Choice == enGameChoices::paper)
        {
            return enWinner::Player2;
        }
        break;
    case enGameChoices::paper:
        if (GameRound.Player2Choice == enGameChoices::Scissors)
        {
            return enWinner::Player2;
        }
        break;
    case enGameChoices::Scissors:
        if (GameRound.Player2Choice == enGameChoices::rock)
        {
            return enWinner::Player2;
        }
        break;
    }
    return enWinner::Player1;
}
enWinner DetermineGameWinner(enCompetitor Competitor, short Player1Wins, short Player2Wins, short ComputerWins, short Draws)
{
    if (Competitor == enCompetitor::PC )
    {
        if (Player1Wins > ComputerWins)
            return enWinner::Player1;
        else if (Player1Wins < ComputerWins)
            return enWinner::Computer;
        else
            return enWinner::NoWinner;
    }
    else // if (Competitor = enCompetitor::Person)
    {
        if (Player1Wins > Player2Wins)
            return enWinner::Player1;
        else if (Player1Wins < Player2Wins)
            return enWinner::Player2;
        else
            return enWinner::NoWinner;
    }
}

stGameResults PlayRound(enCompetitor Competitor, short Rounds)
{
    stGameRound GameRound;
    short ComputerWins = 0, Player1Wins = 0, Player2Wins = 0, Draws = 0;
     if (Competitor == enCompetitor::PC )
    {
        for (int RoundNum = 1; RoundNum <= Rounds; RoundNum++)
        {
            cout << Tabs(1) << "Round [" << RoundNum << "] begins:" << endl;
            GameRound.RoundNum = RoundNum;
            GameRound.ComputerChoice = GetComputerChoice();
            GameRound.Player1Choice = GetPlayerChoice();
            GameRound.RoundWinner = CPWinnerOfRound(GameRound);
            GameRound.RoundWinnerName = WinnerName(GameRound.RoundWinner);

            if (GameRound.RoundWinner == enWinner::Player1)
                ++Player1Wins;
            else if (GameRound.RoundWinner == enWinner::Computer)
                ++ComputerWins;
            else
                ++Draws;

            PrintRoundResults(Competitor,GameRound);
        }
        return {Rounds, Player1Wins, 0, ComputerWins, Draws,
                DetermineGameWinner(Competitor,Player1Wins, Player2Wins,ComputerWins, Draws),
                WinnerName(DetermineGameWinner(Competitor,Player1Wins, Player2Wins,ComputerWins, Draws))};
    }
    else
    {
        for (int RoundNum = 1; RoundNum <= Rounds; RoundNum++)
        {
            cout << Tabs(1) << "Round [" << RoundNum << "] begins:" << endl;
            GameRound.RoundNum = RoundNum;
            cout<<"Player1 ";
            GameRound.Player1Choice = GetPlayerChoice();
            cout << "\nPress Enter and pass the keyboard to Player 2...";
            cin.ignore();
            cin.get();
            system("cls");
            cout<<"Player2 ";
            GameRound.Player2Choice = GetPlayerChoice();
            GameRound.RoundWinner = PPWinnerOfRound(GameRound);
            GameRound.RoundWinnerName = WinnerName(GameRound.RoundWinner);

            if (GameRound.RoundWinner == enWinner::Player1)
                ++Player1Wins;
            else if (GameRound.RoundWinner == enWinner::Player2)
                ++Player2Wins;
            else
                ++Draws;

            PrintRoundResults(Competitor,GameRound);
        }
        return {Rounds, Player1Wins, Player2Wins, 0, Draws,
               DetermineGameWinner(Competitor,Player1Wins, Player2Wins,ComputerWins, Draws),
                WinnerName(DetermineGameWinner(Competitor,Player1Wins, Player2Wins,ComputerWins, Draws))};
    }
}
//====================
// Output Functions
//====================
string WinnerName(enWinner Winner)
{
    string ArrWinner[4] = {"Player1", "Player2", "Computer", "NoWinner"};
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
    case enWinner::Player1:
        system("color 2F"); // Green
        break;

    case enWinner::Player2:
        system("color 1F"); // Blue
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
void PrintRoundResults(enCompetitor Competitor, stGameRound GameRound)
{
     if (Competitor == enCompetitor::PC )
    {
        SetWinnerScreenColour(GameRound.RoundWinner);
        cout << "__________________Round [" << GameRound.RoundNum << "]____________________\n";
        cout << "Player1 Choice  : " << ChoiceName(GameRound.Player1Choice) << endl;
        cout << "Computer Choice: " << ChoiceName(GameRound.ComputerChoice) << endl;
        cout << "Round Winner   : " << GameRound.RoundWinnerName << endl;
        cout << "_______________________________________________________\n";
    }
    else
    {
        SetWinnerScreenColour(GameRound.RoundWinner);
        cout << "__________________Round [" << GameRound.RoundNum << "]____________________\n";
        cout << "Player1 Choice  : " << ChoiceName(GameRound.Player1Choice) << endl;
        cout << "Player2 Choice: " << ChoiceName(GameRound.Player2Choice) << endl;
        cout << "Round Winner   : " << GameRound.RoundWinnerName << endl;
        cout << "_______________________________________________________\n";
    }
}
void PrintGameOverScreen()
{
    cout << Tabs(2) << "_______________________________________________________________\n\n";
    cout << Tabs(2) << "              +++ G A M E  O V E R +++\n";
    cout << Tabs(2) << "_______________________________________________________________\n\n";
}

void PrintFinalGameResults(enCompetitor Competitor, stGameResults GameResults)
{
     if (Competitor == enCompetitor::PC )
    {
        SetWinnerScreenColour(GameResults.GameWinner);

        cout << Tabs(2) << " ____________________________[Game Results]____________________ \n";
        cout << Tabs(2) << " Game rounds         :" << GameResults.TotalRounds << endl;
        cout << Tabs(2) << " Player1 won times   :" << GameResults.Player1WinTimes << endl;
        cout << Tabs(2) << " Computer won times  :" << GameResults.ComputerWinTimes << endl;
        cout << Tabs(2) << " Draw times          :" << GameResults.Draws << endl;
        cout << Tabs(2) << " Final Winner        :" << GameResults.GameWinnerName << endl;
        cout << Tabs(2) << " ______________________________________________________________\n";
    }
    else
    {
        SetWinnerScreenColour(GameResults.GameWinner);

        cout << Tabs(2) << " ____________________________[Game Results]____________________ \n";
        cout << Tabs(2) << " Game rounds        :" << GameResults.TotalRounds << endl;
        cout << Tabs(2) << " Player1 won times  :" << GameResults.Player1WinTimes << endl;
        cout << Tabs(2) << " Player2 won times  :" << GameResults.Player2WinTimes << endl;
        cout << Tabs(2) << " Draw times         :" << GameResults.Draws << endl;
        cout << Tabs(2) << " Final Winner       :" << GameResults.GameWinnerName << endl;
        cout << Tabs(2) << " ______________________________________________________________\n";
    }
}

//====================
// Main Game
//====================
void StartGame()
{
    char PlayAgain;
    do
    {
        ResetScreen();
        enCompetitor Competitor = DetermineCompetitor();
        stGameResults GameResults = PlayRound(Competitor, GetGameRounds());
        PrintGameOverScreen();
        PrintFinalGameResults(Competitor, GameResults);

        cout << endl
             << Tabs(3) << "Do you want to play again ? Y/N ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
