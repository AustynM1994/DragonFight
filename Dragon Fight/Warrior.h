/*
This class has the Warriors health and abilities stored. 
*/

#include <iostream>
#include <ctime> 
#include <cstdlib>  

using namespace std;

//Warrior Class Definition
class Warrior:public Character
{
	private:
		bool shieldWall = false;
		
	public:
		//Default constructor
		Warrior(){}
				
		bool getShieldWall()
		{
			return shieldWall;
		}
		
		void setShieldWall(bool s)
		{
			shieldWall = s;
		}
		
		//Member Functions for ability rolls
		int getSlashDamage()
		{
			return rand() % 11 + 10;
		}
		
};//End of Warrior Class
