/*
This class has the Priests health and abilities 
*/

#include <iostream>
#include <ctime> 
#include <cstdlib>  

using namespace std;

//Priest Class Definition
class Priest:public Character
{	
	public:		
		//Member Functions for ability rolls
		int getSmiteDamage()
		{
			return rand() % 6 + 5;
		}
		
		int getHealAmount()
		{
			return rand() % 6 + 20;
		}
};//End of Priest Class
