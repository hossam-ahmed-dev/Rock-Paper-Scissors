#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enChoice { enRock = 1, enPaper = 2, enScissors = 3 };

enum enWinner { enPlayer = 1, enComputer = 2, enNoWinner = 3 };

struct stRoundInfo
{
    enChoice playerChoice;
    enChoice computerChoice;
    enWinner roundWinner;
};

struct stGameInfo
{
    short numberOfRounds = 0;
    short playerWonTimes = 0;
    short computerWonTimes = 0;
    short drawTimes = 0;
    enWinner finalWinner;
};

string printTabs(short numberOfTabs)
{
    string tabs = "";

    for (short i = 1; i <= numberOfTabs; i++)
    {
        tabs += "\t";
    }

    return tabs;
}

void resetScreen()
{
    system("CLS");
    system("color 07");
}

void changeScreenWinnerColor(enWinner winner)
{
    if(winner == enWinner::enPlayer)
        system("color 2F");
    else if (winner == enWinner::enComputer)
    {
        system("color 4F");
        cout << "\a";
    }
    else
        system("color 6F");
}

bool isNumberInRange(short number, short from, short to)
{
    return (number >= from && number <= to);
}

short readNumberOfRounds()
{
    short numberOfRounds = 0;

    do
    {
        cout << "How Many Rounds 1 To 10 ? ";
        cin >> numberOfRounds;

    } while (!isNumberInRange(numberOfRounds, 1, 10));

    return numberOfRounds;
}

enChoice readPlayerChoice()
{
    short choice = 0;

    do
    {
        cout << "\nYour Choice: [1]: Rock, [2]: Paper, [3]:Scissors ? ";
        cin >> choice;

    } while (!isNumberInRange(choice, 1, 3));

    return (enChoice)choice;
}

short getRandomNumber(short from, short to)
{
    short randomNumber = rand() % (to - from + 1) + from;
    return randomNumber;
}

enChoice getComputerChoice()
{
    return (enChoice)getRandomNumber(1, 3);
}

enWinner getRoundWinner(enChoice playerChoice, enChoice computerChoice)
{
    if (playerChoice == computerChoice)
        return enWinner::enNoWinner;

    switch (playerChoice)
    {
    case enChoice::enRock:
        if (computerChoice == enChoice::enScissors)
            return enWinner::enPlayer;
        break;

    case enChoice::enPaper:
        if (computerChoice == enChoice::enRock)
            return enWinner::enPlayer;
        break;

    case enChoice::enScissors:
        if (computerChoice == enChoice::enPaper)
            return enWinner::enPlayer;
        break;
    }

    return enWinner::enComputer;
}

stRoundInfo playRound(short roundNumber)
{
    stRoundInfo roundInfo;

    cout << "\n\n\n\nRound [" << roundNumber << "] Begins : ";
    roundInfo.playerChoice = readPlayerChoice();
    roundInfo.computerChoice = getComputerChoice();
    roundInfo.roundWinner = getRoundWinner(roundInfo.playerChoice, roundInfo.computerChoice);

    return roundInfo;
}

string getChoiceName(enChoice choice)
{
    string arrChoice[3] = { "Rock", "Paper" , "Scissors" };
    return arrChoice[choice - 1];
}

string getWinnerName(enWinner winner)
{
    string arrWinner[3] = { "Player", "Computer" , "No Winner" };
    return arrWinner[winner - 1];
}

void printRoundInfo(stRoundInfo roundInfo, short roundNumber)
{
    cout << "\n" << printTabs(4) << "____________Round[" << roundNumber << "]____________" << endl;
    cout << "\n" << printTabs(4) << "Player Choice    : " << getChoiceName(roundInfo.playerChoice);
    cout << "\n" << printTabs(4) << "Computer Choice  : " << getChoiceName(roundInfo.computerChoice);
    cout << "\n" << printTabs(4) << "Round Winner     : [" << getWinnerName(roundInfo.roundWinner) << "] ";
    cout << "\n" << printTabs(4) << "________________________________";

    changeScreenWinnerColor(roundInfo.roundWinner);
}

enWinner getFinalWinner(short playerWonTimes, short computerWonTimes)
{
    if (playerWonTimes > computerWonTimes)
        return enWinner::enPlayer;
    else if (computerWonTimes > playerWonTimes)
        return enWinner::enComputer;
    else
        return enWinner::enNoWinner;
}

stGameInfo getGameInfo(short playerWonTimes, short computerWonTimes, short drawTimes, short numberOfRounds)
{
    stGameInfo gameInfo;

    gameInfo.numberOfRounds = numberOfRounds;
    gameInfo.playerWonTimes = playerWonTimes;
    gameInfo.computerWonTimes = computerWonTimes;
    gameInfo.drawTimes = drawTimes;
    gameInfo.finalWinner = getFinalWinner(gameInfo.playerWonTimes, gameInfo.computerWonTimes);

    return gameInfo;
}

void printGameOverScreen()
{
    cout << "\n\n\n";
    cout << printTabs(3) << "_________________________________________________________" << endl;
    cout << endl;
    cout << printTabs(3) << "                +++ G a m e  O v e r +++";
    cout << endl;
    cout << printTabs(3) << "_________________________________________________________" << endl;
    cout << "\n";
}

void printGameInfo(stGameInfo gameInfo)
{
    printGameOverScreen();

    cout << "\n" << printTabs(3) << "_____________________[Game Results] _____________________";
    cout << "\n" << printTabs(3) << "Game Rounds : " << gameInfo.numberOfRounds;
    cout << "\n" << printTabs(3) << "Player Won Times : " << gameInfo.playerWonTimes;
    cout << "\n" << printTabs(3) << "Computer Won Times  : " << gameInfo.computerWonTimes;
    cout << "\n" << printTabs(3) << "Draw Times : " << gameInfo.drawTimes;
    cout << "\n" << printTabs(3) << "Final Winner : " << getWinnerName(gameInfo.finalWinner);
    cout << "\n" << printTabs(3) << "__________________________________________________________";

    changeScreenWinnerColor(gameInfo.finalWinner);
}

stGameInfo playGame(short numberOfRounds)
{
    stRoundInfo roundInfo;
    short playerWonTimes = 0, computerWonTimes = 0, drawTimes = 0;

    for (short roundNumber = 1; roundNumber <= numberOfRounds; roundNumber++)
    {
        roundInfo = playRound(roundNumber);
        printRoundInfo(roundInfo, roundNumber);

        if (roundInfo.roundWinner == enWinner::enPlayer)
            playerWonTimes++;
        else if (roundInfo.roundWinner == enWinner::enComputer)
            computerWonTimes++;
        else
            drawTimes++;
    }

    return getGameInfo(playerWonTimes, computerWonTimes, drawTimes, numberOfRounds);
}

void startGame()
{
    char playAgain = 'y';

    do
    {
        resetScreen();
        stGameInfo gameInfo;
        gameInfo = playGame(readNumberOfRounds());
        printGameInfo(gameInfo);

        cout << "\n\n" << printTabs(3) << "Do You Want To Play Again ? Y / N ? ";
        cin >> playAgain;

    } while (tolower(playAgain) == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}