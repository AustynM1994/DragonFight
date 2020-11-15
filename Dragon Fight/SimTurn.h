#include <iostream>
#include<limits>
#include "Main.h" //This is so I can display the correct UI while in this class
using namespace std;

class SimTurn
{		
	private:
		int actionRoll;
		int playerAction;
		int rAttack;
		int rTarget;
		
	public:
		template <class W, class P, class D>		
		void playerTurn(W& w, P& p, D& d)
		{		
			do
			{
				cin >> playerAction;
				
				if(playerAction == 1) //Warrior Attacks
				{
					checkIfDead(w, p, playerAction);//Checking if the warrior is dead before the turn
										
					//If the Warrior used shield wall he can't attack this turn as well
					if(w.getShieldWall() == true && p.getHealth() > 0)
					{
						cout << "The Warrior cannot attack and protect the Priest at the same time! Enter to continue.";
						cin.get();
						cin.get();
						playGame();
						return;
					}
					
					system("CLS");
					displayUI("UI\\Warrior.txt");
					
					if(d.getFlying() == true) //If the Dragon is flying the Warrior will miss his attack
					{
						cout << "\nThe Warrior misses the Dragon! Enter to continue.";
						cin.get();
						return;
					}
					actionRoll = w.getSlashDamage();
					d.setHealth(d.getHealth() - actionRoll);
					cout << "The Warrior Slashes the dragon for " << actionRoll << " damage! Enter to continue.";
					cin.get();
					return;
				}
				else if (playerAction == 2) //Warrior uses ShieldWall
				{
					checkIfDead(w, p, playerAction);
					//If the warrior used shield wall last turn he will block the attack
					if(w.getShieldWall() == true)
					{
						cout << "The Warrior is already protecting the Priest! Enter to continue.";
						cin.get();
						cin.get();						
						playGame();
						return;
					}
					
					w.setShieldWall(true);
					return;
				}
				else if (playerAction == 3) //Priest heals the Warrior
				{
					checkIfDead(w, p, playerAction);
					actionRoll = p.getHealAmount();
					system("CLS");
					displayUI("UI\\Priest.txt");
					cout << "\nThe Priest heals the Warrior for " << actionRoll << " health! Enter to continue.";
					if(actionRoll + w.getHealth() > 100)
					{
						w.setHealth(100); 
					}
					else
					{
						w.setHealth(actionRoll + w.getHealth());	
					}
					cin.get();
					return;
				}
				else if (playerAction == 4) //Priest heals himself
				{
					checkIfDead(w, p, playerAction);
					actionRoll = p.getHealAmount();
					system("CLS");
					displayUI("UI\\Priest.txt");
					cout << "\nThe Priest heals himself for " << actionRoll << " health! Enter to continue.";
					if(actionRoll + p.getHealth() > 75)
					{
						p.setHealth(75); 
					}
					else
					{
						p.setHealth(actionRoll + p.getHealth());	
					}
					cin.get();
					return;
				}
				else if (playerAction == 5) //Priest casts a smite
				{
					checkIfDead(w, p, playerAction);
					actionRoll = p.getSmiteDamage();
					d.setHealth(d.getHealth() - actionRoll);
					system("CLS");
					displayUI("UI\\Priest.txt");
					cout << "\nThe Priest Smites the dragon for " << actionRoll << " damage! Enter to continue.";
					cin.get();
					return;
				}
				else
				{
					cout << "\nInvalid Input. Enter a number above to use the ability: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}while (playerAction != 1 && playerAction != 2 && playerAction != 3 && playerAction != 4 && playerAction != 5);
		}
		
		template <class W, class P, class D>	
		void dragonTurn(W& w, P& p, D& d, int rAttack, int rTarget)
		{	
			//Check if dragon is flying, if true then he will breath fire and end his turn
			if(d.getFlying() == true)
			{
				//If the warrior used shield wall last turn he will block the attack
				if(w.getShieldWall() == true)
				{
					warriorShieldWall(w, d, "UI\\DragonBreath.txt");
					return;
				}
				actionRoll = d.getFireBreathDamage();
				w.setHealth(w.getHealth() - actionRoll);
				p.setHealth(p.getHealth() - actionRoll);
				system("CLS");
				displayUI("UI\\DragonBreath.txt");
				cout << "\nThe Dragon breathes fire onto the Warrior and Priest for " << actionRoll << " damage! Enter to continue.";
				cin.get();
				d.setFlying(false);
				return;
			}
			
			//Check if the dragon is regenerating, if true then he will regenerate health and end his turn
			if(d.getRegen() == true)
			{
				actionRoll = d.getRegenerationAmount();
				
				if(w.getShieldWall() == true)
				{
					warriorShieldWall(w, d, "UI\\DragonRegen.txt");
				}
				
				if(actionRoll + d.getHealth() > 500)
				{
					system("CLS");
					displayUI("UI\\DragonRegen.txt");
					cout << "The Dragon heals himself for " << actionRoll << " health!";
					d.setHealth(500);
					d.setRegen(false);
					cin.get();
					return;
				}
				else
				{
					system("CLS");
					displayUI("UI\\DragonRegen.txt");
					cout << "The Dragon heals himself for " << actionRoll << " health!";
					d.setHealth(actionRoll + d.getHealth());
					d.setRegen(false);
					cin.get();
					return;
				}
			}
			
			//If statements for dragon attacking and the target
			if(rAttack >= 0 && rAttack <= 50) //Bite attack
			{
				//If the warrior used shield wall last turn he will block the attack
				if(w.getShieldWall() == true)
				{
					warriorShieldWall(w, d, "UI\\DragonBite.txt");
					return;
				}
				
				if(rTarget == 1 && w.getHealth() > 0)
				{
					actionRoll = d.getBiteDamage();
					w.setHealth(w.getHealth() - actionRoll);
					system("CLS");
					displayUI("UI\\DragonBite.txt");
					cout << "\nThe Dragon bites the Warrior for " << actionRoll << " damage! Enter to continue.";
					cin.get();
				}
				else if (rTarget == 2 && p.getHealth() > 0)
				{
					actionRoll = d.getBiteDamage();
					p.setHealth(p.getHealth() - actionRoll);
					system("CLS");
					displayUI("UI\\DragonBite.txt");
					cout << "\nThe Dragon bites the Priest for " << actionRoll << " damage! Enter to continue.";
					cin.get();
				}
			}
			else if (rAttack >= 51 && rAttack <= 80) //Breath Attack
			{
				d.setFlying(true);
				system("CLS");
				displayUI("UI\\DragonFlying.txt");
				cout << "\nThe Dragon takes flight and takes a deep breath! Enter to continue.";
				cin.get();
			}
			else if (rAttack >= 81 && rAttack <= 100) //Regeneration
			{
				d.setRegen(true);
				system("CLS");
				displayUI("UI\\DragonRegen.txt");
				cout << "\nThe Dragon starts to regenerate its health! Enter to continue." 	;
				cin.get();	
			}
		}
		
		template <class W, class D>
		void warriorShieldWall(W& w, D& d, string uI)
		{
			system("CLS");
		    displayUI(uI);
			cout << "\nThe Warrior protects himself and the Priest from damage with his shield! Enter to continue.";
			w.setShieldWall(false);
			d.setFlying(false);
			cin.get();
		}
		
		template <class W, class P>
		void checkIfDead(W& w, P& p, int playerAction)
		{
			//If the Warrior is dead he cannot attack
			if(w.getHealth() <= 0 && playerAction == 2 || w.getHealth() <= 0 && playerAction == 1)
			{
				cout << "The Warrior is dead and cannot attack, RIP. Enter to continue";
				cin.get();
				cin.get();
				playGame();
				return;
			}
			//If the Priest is dead he cannot attack or heal
			else if(p.getHealth() <= 0 && playerAction == 3 || p.getHealth() <= 0 && playerAction == 4 || p.getHealth() <= 0 && playerAction == 5)
			{
				cout << "The Priest is dead and cannot attack or heal, RIP. Enter to continue";
				cin.get();
				cin.get();
				playGame();
				return;
			}
			//If the Warrior is dead the Priest cannot heal him
			else if(w.getHealth() <= 0 && playerAction == 3)
			{
				cout << "The Warrior is dead and cannot be healed, RIP. Enter to continue";
				cin.get();
				cin.get();
				playGame();
				return;
			}
		}
};
