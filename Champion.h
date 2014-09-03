/*****************************************
Data Record class that will hold the data
for each champion. Only the wrapper will
be able to access the data.

Created by Ye Aung
*****************************************/

#ifndef CHAMPION_H
#define CHAMPION_H

#define MAX_ABILITY 5
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Stats
{
    int attack,
		defense,
		abilityP,
		difficulty;
    Stats() {   attack = defense = abilityP = difficulty = 0;  }
};

class Champion
{
private:
	string Name;
	string Ability[MAX_ABILITY];
	string Role;
	string Type;
	Stats char_Stats;
	bool freeOrNot;	

public:
	Champion(){
		Name = Role = Type = ""; freeOrNot = 0;
		for (int i = 0; i < MAX_ABILITY; i++) Ability[i] = "";
	}
	void setName(const string N)	       {   Name = N;	}
	void setAbility(const string A[])      {   for(int i = 0; i < MAX_ABILITY; i++) Ability[i] = A[i];	}
	void setRole(const string R)           {   Role = R;	}
	void setType(const string T)           {   Type = T;	}
	void setStats(const Stats C)           {   char_Stats = C;	}
	void setFreeOrNot(const bool b)	       {   freeOrNot = b; }

    string  getName() const	               {   return Name;	        }
	string  getAbility(int n) const        {   return Ability[n];	}
	string  getRole() const                {   return Role;	        }
	string  getType() const                {   return Type;	}
	Stats   getStats() const               {   return char_Stats;	}
	bool	getFreeOrNot() const		   { return freeOrNot;     }

	bool operator < (const Champion &right)
	{
		return this->getName() < right.getName();
	}

	bool operator > (const Champion &right)
	{
		return (this->getName() > right.getName());
	}

	bool operator == (const Champion &right)
	{
		return (this->getName() == right.getName());
	}

	Champion &operator=(const Champion &right)
	{
		string temp[MAX_ABILITY];
		this->setName(right.getName());
		for (int i = 0; i < MAX_ABILITY; i++)
			temp[i] = right.getAbility(i);
		this->setAbility(temp);
		this->setRole(right.getRole());
		this->setType(right.getType());
		this->setStats(right.getStats());
		this->freeOrNot = right.freeOrNot;
		return *this;
	}

};

#endif
