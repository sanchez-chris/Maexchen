#include<iostream>
#include<ctime>
#include <string>


#include "functions.h"


using namespace std;

class Player
{
private:

	//Players have a variable that, if true, is human and if not, is cpu's
	bool IsHuman = true;

	int rollthedice()
	{
		int dice1, dice2;
		int number;
		srand(time(0));
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;

		if (dice1 < dice2) {
			number = dice2 * 10 + dice1;
		}
		else if (dice1 > dice2) {
			number = dice1 * 10 + dice2;
		}
		else { // dice1 = dice2 
			number = dice1 * 10 + dice2;
		}

		return number;
	}

	int ValueOfDice(int diceResult)
	{
		//We assign a value for the number of dice, depending on the scale from lowest to highest: 
		//31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65, 11, 22, 33, 44, 55, 66, 21 (axen).

		int valueNumber = -1;

		switch (diceResult) {
		case 31: valueNumber = 1; break;
		case 32: valueNumber = 2; break;
		case 41: valueNumber = 3; break;
		case 42: valueNumber = 4; break;
		case 43: valueNumber = 5; break;
		case 51: valueNumber = 6; break;
		case 52: valueNumber = 7; break;
		case 53: valueNumber = 8; break;
		case 54: valueNumber = 9; break;
		case 61: valueNumber = 10; break;
		case 62: valueNumber = 11; break;
		case 63: valueNumber = 12; break;
		case 64: valueNumber = 13; break;
		case 65: valueNumber = 14; break;
		case 11: valueNumber = 15; break;
		case 22: valueNumber = 16; break;
		case 33: valueNumber = 17; break;
		case 44: valueNumber = 18; break;
		case 55: valueNumber = 19; break;
		case 66: valueNumber = 20; break;
		case 21: valueNumber = 21; break;
		default:
			valueNumber = -1;
		};

		return valueNumber;
	}


public:
	int ID = 0;
	int PenaltyPoints = 0;

	Player()
	{

	}

	Player(int _ID, bool _IsHuman)
	{
		ID = _ID;
		IsHuman = _IsHuman;
	}

	bool DoTurn(Player* nextPlayer)
	{
		cout << "\nTurn of player " << ID << endl;

		//Throw Dice
		int diceResult;
		diceResult = rollthedice();

		//If dice result is 21, turn ends and turns order reverse
		if (diceResult == 21)
		{
			cout << "Result was Axen (21). Turn reversal!" << endl;
			return true;
		}

		//Declare "Lie" number
		int declaredNumber;
		if (IsHuman)
		{
			//If the player is a human, we ask the number
			cout << "The dice throws result: " << diceResult << " (Value " << ValueOfDice(diceResult) << "). What number do you want to declare? "; cin >> declaredNumber;

			while (ValueOfDice(declaredNumber) < 0)
			{
				cout << "That result is impossible! Input a valid result (31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65, 11, 22, 33, 44, 55, 66, 21)  "; cin >> declaredNumber;
			}
		}

		else
		{
			//If the player is computer-controlled, it throws dice in secret
			declaredNumber = rollthedice();
			cout << "The computer throws its dice in secret." << endl;
		}

		//Next player declares truth or lie
		if (nextPlayer->ResolveLie(declaredNumber))
		{
			//Next player accepted our result as true. We do nothing.
		}
		else
		{
			//Next player thought we lied!

			int RealValue = ValueOfDice(diceResult);
			int DeclaredValue = ValueOfDice(declaredNumber);

			if (RealValue >= DeclaredValue)
			{
				//The real number (diceResult)'s value was same or bigger than my number (yourNumber)'s value. The other player (nextPlayer) gets penalty.
				nextPlayer->PenaltyPoints += 1;
				cout << "Fail! The result of the dice was of same or bigger value. Player " << nextPlayer->ID << " receives 1 Penalty Point!" << endl;
			}
			else
			{
				//My lie was discovered and the real number (diceResult)'s value was smaller than my number (yourNumber)'s value. I get penalty.
				PenaltyPoints += 1;
				cout << "Lie discovered! The result of the dice was of smaller value. Player " << ID << " receives 1 Penalty Point!" << endl;
			}

		}

		return false;
	}

	bool ResolveLie(int declaredNumber)
	{
		if (IsHuman == false)
		{
			//If computer, we believe the lie or not at random

			bool believe = (bool)(rand() % 2);
			if (believe)
				cout << "Player " << ID << ": " << "Decides to believe the previous player." << endl;
			else
				cout << "Player " << ID << ": " << "Decides to NOT believe the previous player." << endl;

			return believe;
		}
		else
		{
			//If human, we ask for discover the lie: Y/N
			char input;
			cout << "Player " << ID << ": The previous player says he got a result of " << declaredNumber << " (Value: "<< ValueOfDice(declaredNumber) << "). Do you think this is true? Y/N: "; cin >> input;
			if (input == 'Y' || input == 'y')
			{
				return true; //I think he said the truth!
			}

			else
			{
				return false; //I think he lied!
			}
		}
	}
};

//Globals Variables
Player players[100];
int numberPlayers = -1;
int roundDirection = 1; //Turns order: 1 means 1->2->3->4->1[...] and -1 means 4->3->2->1->4[...]
int currentPlayerIndex = 0;





//General Functions
void ShowInstructions()
{
	char lenguage;

	const string instruccionsGerman =

		"\nMaexchen ist ein Wuerfelspiel, das mit mindestens vier Spielern gespielt wird, die immer der Reihe\n"
		"nach in fester Reihenfolge mit zwei Wuerfeln verdeckt wuerfeln und sich das Ergebnis selbst\n"
		"anschauen, ohne es den anderen Spielern zu zeigen. Dann geben Sie ihr Wuerfelergebnis allen\n"
		"Spielern bekannt. Dabei koennen sie das tatsächliche Ergebnis nennen oder sie koennen luegen.\n"
		"\nJedem Wurf wird ein bestimmter Wert zugeordnet:\n\n"
		"\n1. Jeder der beiden Wuerfel zeigt eine zufaellige Zahl von eins bis sechs.\n\n"
		"\n2. Wurden zwei unterschiedliche Zahlen gewuerfelt, wird immer die hoehere Zahl vorne\n"
		"geschrieben. So gibt es also den Wurf 64, aber nicht 46. Der Wert ergibt sich durch\n"
		"nummerische Sortierung. Alle moeglichen Wuerfe nach dieser Regel vom kleinsten bis zum\n"
		"groessten Wert sind damit : 31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65.\n\n"
		"\n3. Zwei gleiche Zahlen (Pasch) werden immer hoeher bewertet als die Wuerfe mit\n"
		"unterschiedlichen Zahlen. Die moeglichen Wuerfe nach dieser Regel vom kleinsten bis zum\n"
		"groessten Wert sind damit: 11, 22, 33, 44, 55, 66.\n\n"
		"\n4. Der Wurf mit dem hoechsten Wert ist die 21 und heisst Maexchen.\n\n"
		"Hier sind zusammengefasst alle moeglichen Wuerfe vom kleinsten bis zum groessten Wert:\n"
		"31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65, 11, 22, 33, 44, 55, 66, 21.\n\n"
		"Der wesentliche Punkt des Spiels ist, dass ein Spieler, der den Wert seines Wurfs bekannt gibt,\n"
		"immer einen hoeheren Wert nennen muss als der vorhergehende Spieler.Wie oben beschrieben,\n"
		"kann er den tatsaechlichen Wert nennen oder er kann luegen, aber er muss immer einen groesseren\n"
		"Wert angeben.\n"
		"\nDer naechste in der Reihe muss nun entscheiden, ob er das Ergebnis glaubt oder nicht. Glaubt er\n"
		"das Ergebnis, nimmt er die Wuerfel, ohne sie aufzudecken, wuerfelt selbst und sagt wieder einen\n"
		"groesseren Wert an.\n"
		"Glaubt er dem Vorgaenger nicht, werden die Wuerfel aufgedeckt.Wurde die Wahrheit gesagt,\n"
		"bekommt der Zweifler einen Strafpunkt.Wurde gelogen, gibt es zwei Faelle:\n\n"
		"\n1. Was das Wuerfelereignis niedriger als der angesagt Wert, bekommt der Wuerfler einen\n"
		"Strafpunkt, der Nachfolger beginnt mit einem neuen Spiel.\n"
		"\n2. War das Wuerfelereignis höher als der angesagte Wert, bekommt der Zweifler den\n"
		"Strafpunkt.\n\n"
		"\nBeispiel : Spieler 1 sagt den Wert 63 an. Spieler 2 glaubt ihm, wuerfelt 22 sagt aber den Wert 11\n"
		"an. Wenn Spieler 3 ihm nicht geglaubt, bekommt er trotz der Luege selbst den Strafpunkt, da der\n"
		"angesagte Wert geringer als der tatsaechlich gewuerfelte ist.\n"
		"Nach dem Aufdecken ist derjenige an der Reihe mit Wuerfeln, der das Aufdecken verlangt hat. Es\n"
		"beginnt ein neues Spiel, das heisst der Spieler kann einen beliebigen Wert ansagen, richtig oder\n"
		"gelogen. Nur bei Maexchen (siehe unten) wird die Spielrichtung geaendert.\n\n"
		"\nBei Maexchen (21) muss aufgedeckt werden. Auch hier gilt : hat der Vorgaenger die Wahrheit\n"
		"gesprochen, bekommt der Nachfolger den Strafpunkt, war es gelogen, bekommt der Wuerfler den\n"
		"Strafpunkt. Nach Maexchen(tatsaechlich oder gelogen) wird die Spielrichtung geaendert.\n"
		"Spielrichtung aendern heisst: hat Spieler 3 Maexchen gesagt oder geworfen, Spieler 4 aufgedeckt,\n"
		"beginnt Spieler 2 mit dem neuen Spiel und gibt es an Spieler 1 weiter.\n\n\n\n\n\n";


	const string instruccionsEnglish =

		"\nThe goal is to implement the game Maexchen.\n"
		"Maexchen is a dice game, which is played with at least four players, who always follow the\n"
		"after in fixed order with two dice coveredand the result itself\n"
		"without showing it to the other players.Then you give your dice result to all\n"
		"known to players.They can tell the actual result or they can lie.\n\n"
		"A certain value is assigned to each roll of the dice:\n\n"
		"1: Each of the dice will roll a random number from one to six.\n\n"
		"2. If two different numbers are thrown, the higher number is always in front\n"
		"written.So there's the 64, but not the 46.\n"
		"All possible throws according to this rule from the smallest to the\n"
		"highest values are this: 31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65.\n\n"
		"3. two identical numbers (Pasch) are always rated higher than the litters with\n"
		"different numbers.The possible throws according to this rule from the smallest to the\n"
		"the largest value are this : 11, 22, 33, 44, 55, 66.\n\n"
		"4: The litter with the highest value is 21 and is called Axen.\n"
		"Here are summarized all possible throws from the smallest to the highest value:\n"
		"31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65, 11, 22, 33, 44, 55, 66, 21.\n\n"
		"The essential point of the game is that a player who announces the value of his roll,\n"
		"must always name a higher value than the previous player.As described above,\n"
		"he can tell the real value or he can lie, but he must always enter a value.\n\n"
		"The next in the row must now decide whether to believe the result or not. If he believes\n"
		"the result, he takes the dice without revealing them, rolls the dice himselfand says again a\n"
		"greater value.\n\n"
		"If he does not believe the previous one, the dice are revealed. If the truth was told,\n"
		"the doubter gets a penalty point. If a lie was told, there are two cases:\n\n"
		"1: If the roll of the dice event is less than the declared value, the dealer receives a\n"
		"penalty point, the next starts a new game.\n"
		"2. If the dice event was higher than the announced value, the doubter gets the\n"
		"Penalty point.\n\n"
		"Example : Player 1 announces the value 63. Player 2 believes him, but rolls 22 and announces 11\n"
		"on. If player 3 does not believe him, he gets the penalty point despite the lie itself, because the\n"
		"is lower than the value actually thrown on the dice.\n"
		"After the roll is revealed, it is the turn of the dice that has requested the reveal.It\n"
		"starts a new game, i.e.the player can announce any value, correct or\n"
		"lied. Only with axes (21) the direction of play is changed.\n\n"
		"In the case of axes (21), you must reveal. Also here applies: if the predecessor has the truth\n"
		"the successor gets the penalty point, if it was a lie, the thrower gets the\n"
		"Penalty point. After MAX (actual or lied) the direction of play is changed.\n"
		"Changing the direction of play means: player has said or thrown 3 axes, player 4 is revealed,\n"
		"player 2 starts the new game and passes it on to player 1.\n\n\n\n\n\n";



	cout << "Wellcome to Maexchen, Do you want the instructions in German or English? G/E. Press another key if you want to skip the instruccions."; cin >> lenguage;

	if (lenguage == 'G' || lenguage == 'g') {
		cout << instruccionsGerman;
	}

	else if (lenguage == 'E' || lenguage == 'e') {
		cout << instruccionsEnglish;
	}

	else {
		cout << "You chose to skip the instruccions. Enjoy!\n\n\n";

	}

}

bool ConfigurePlayers()
{
	int humanPlayers;

	cout << "How many players are you?: "; cin >> humanPlayers;
	if (humanPlayers < 3)
	{
		cout << "the minimum number of players is 4, if you choose 3, one player will be the computer. ";
		return false;
	}

	//If you choose more than 3 humans, then all of them are human. But if you choose 4 players, one will be the computer
	if (humanPlayers > 3)
		numberPlayers = humanPlayers;
	else
		numberPlayers = 4;


	//we create the Players array with gamer1, gamer2, gamer3...
	for (int i = 0; i < numberPlayers; i++)
	{
		//If the current index of player is above the number of humans, then it's a computer. 
		bool isHuman = (i < humanPlayers);

		//When creating a player we declare its ID and if it's computer-controlled
		Player newPlayer(i + 1, isHuman);
		players[i] = newPlayer;
	}


	cout << "This game will be for " << numberPlayers << " players " << "(" << (numberPlayers - humanPlayers) << " computer)" << endl;

	return true;
}


int NextPlayerIndex()
{
	int nextPlayerIndex;

	nextPlayerIndex = currentPlayerIndex + roundDirection;

	if (nextPlayerIndex < 0)
	{
		nextPlayerIndex = numberPlayers - 1;
	}
	else if (nextPlayerIndex >= numberPlayers)
	{
		nextPlayerIndex = 0;
	}


	return nextPlayerIndex;
}

void Round()
{
	int playersPlayedInThisRound = 0;

	while (playersPlayedInThisRound < numberPlayers)
	{
		bool reverse = false;

		//Execute turn of current player (it receives a pointer to next player)
		reverse = players[currentPlayerIndex].DoTurn(&players[NextPlayerIndex()]);
		if (reverse)
		{
			roundDirection = -(roundDirection);
		}

		//Increase turn (controlling the limits)
		currentPlayerIndex = NextPlayerIndex();

		//End of round: when all players played
		playersPlayedInThisRound++;
	}
}

void ShowPlayersScore()
{
	cout << "\nThese are the current points: " << endl;

	for (int i = 0; i < numberPlayers; i++)
	{
		cout << "Player " << players[i].ID << ": " << players[i].PenaltyPoints << " penalty points\n";
	}
}

bool EndGameQuestion()
{
	char input;
	cout << "\nDo you want to finish the game? Y/N: "; cin >> input;
	if (input == 'Y' || input == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}







