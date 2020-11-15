/* 
This will be a game where you fight a dragon controlling a warrior and a priest. 
	None of the ascii art is mine, I found them online.
*/
#include <iostream>
#include <ctime> 
#include <cstdlib>  
#include "DisplayUI.h"
#include "Character.h"
#include "Warrior.h"
#include "Priest.h"
#include "Dragon.h"
#include "SimTurn.h"

//This function displays the Main Menu
void displayUI(string gameUI);

//This function goes through the game
void playGame();

//This function checks if the player wants to continue to play
void continueGameCheck();

//This function will display the warrior, priest and dragons health
void healthDisplay();

//This function will let the player take a turn
void playerTurn();

//This function will let the dragon take a turn
void dragonTurn();

//This function will check if the player has won
void checkGameOver();

//This function will check what characters have died and display the correct battle scene
string displayBattleScene();

//Global instance of all classes
Warrior war;
Priest priest;
Dragon dragon;
SimTurn simT;

int main(int argc, char** argv) 
{
	//Sets the initial health of the characters and allows random to be used
	srand(time(0));
	war.setHealth(100);
	priest.setHealth(75);
	dragon.setHealth(500);  
	
	//Display the main menu
	displayUI("UI\\MainMenu.txt");
	cin.get();
	playGame();	
	return 0;
}

void displayUI(string gameUI)
{	
	//Vector to hold the returned vector of getData
	vector<string> vGameUI = getData(gameUI);
	
	//Dump vector into file
	for(int n = 0; n < vGameUI.size(); n++)
	{
		//Display Names
		cout << vGameUI.at(n) << endl;
	}//End of for
}//End of displayUI(string gameUI)

void playGame()
{
	int rAttack = rand() % 101;
	int rTarget = rand() % 2 + 1;
	
	system("CLS");
	displayUI(displayBattleScene());
	healthDisplay();
	displayUI("UI\\PlayerActionsUI.txt");
	simT.playerTurn(war, priest, dragon); //Start the players turn
	cin.get();
	checkGameOver(); //Checks after the players turn to see if the Dragon died
	simT.dragonTurn(war, priest, dragon, rAttack, rTarget); //Starts the dragons turn
	checkGameOver(); //Checks after Dragons turn to see if player lost
	playGame(); //Plays another turn
}

void continueGameCheck()
{
	string strCheck = "";
	cin >> strCheck;
	
	do
	{
		if (strCheck == "Y" || strCheck == "y")
		{
			cout << "Have Fun!";//Game is reset
			war.setHealth(100);
			priest.setHealth(75);
			dragon.setHealth(500);
			playGame();
		}
		else if (strCheck != "Y" && strCheck != "y" && strCheck != "N" && strCheck != "n")
		{
			cout << strCheck << " Invalid Choice. Y/N to continue\n";
			cin >> strCheck;
		}
	}while (strCheck != "Y" && strCheck != "y" && strCheck != "N" && strCheck != "n");
	
	cout << "Goodbye!";//The player ended the game and the program is closed
	exit(0);
}

void healthDisplay()
{
	if(priest.getHealth() <= 0)
	{
		priest.setHealth(0);
	}
	else if (war.getHealth() <= 0)
	{
		war.setHealth(0); 
	}
	cout << "  Health:" << priest.getHealth() << "/75" << "  Health:" << war.getHealth() << "/100"<< "\t\t   Health:" << dragon.getHealth() << "/500" << endl;
}

void checkGameOver()
{
	if(dragon.getHealth() <= 0)
	{
		system("CLS");
		displayUI("UI\\Victory.txt");
		cout << "\n\t\tYou win! Play Again? Y/N\n";
		continueGameCheck();
	}
	else if(war.getHealth() <= 0 && priest.getHealth() <= 0)
	{
		system("CLS");
		displayUI("UI\\Defeat.txt");
		cout << "\n\t\tYou Lose! Play Again? Y/N\n";
		continueGameCheck();
	}
}//End of checkForWin()

string displayBattleScene()
{
	if (war.getHealth() > 0 &&  priest.getHealth() > 0)
	{
		return "UI\\TwoAliveBattleScene.txt";
	}
	else if (war.getHealth() <= 0)
	{
		return "UI\\WarriorDeadBattleScene.txt";
	}
	else if (priest.getHealth() <= 0)
	{
		return "UI\\PriestDeadBattleScene.txt";
	}
}//End of displayBattleScene()
