/*
This class has the Warriors health and abilities stored. 
*/

#include <iostream>
#include <ctime> 
#include <cstdlib>  

using namespace std;

//Character Class Definition
class Character
{
	private:
		int health = 100;
		
	public:
		//Default constructor
		Character(){}
		
		//Accessors and Mutators
		int getHealth()
		{
			return health;
		}
		
		void setHealth(int h)
		{
			health = h;
		}		
};//End of Character Class
