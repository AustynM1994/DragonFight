/*
This class has the Dragons health and abilities 
*/

#include <iostream>
#include <ctime> 
#include <cstdlib>  

using namespace std;

//Dragon Class Definition
class Dragon:public Character
{
	private:
		bool flying = false;
		bool regen = false;
		
	public:		
		bool getRegen()
		{
			return regen;
		}
		
		void setRegen(bool r)
		{
			regen = r;
		}
		
		bool getFlying()
		{
			return flying;
		}
		
		void setFlying(bool f)
		{
			flying = f;
		}
		
		//Member Functions for ability rolls
		int getBiteDamage()
		{
			return rand() % 25 + 10;
		}
		
		int getFireBreathDamage()
		{
			return rand() % 20 + 30;
		}
		
		int getRegenerationAmount()
		{
			return rand() % 15 + 30;
		}
};//End of Dragon Class
