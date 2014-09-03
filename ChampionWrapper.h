/*
 Wrapper concept that will create a heap for champion data record and point to it
 //Note: When sharing data with another data structure or even working with address
 it's important not to trigger the destructor whenever the function returns the
 Wrapper itself which is why there's a comdition to do the destructor
 
 By Ye Aung
 */

#ifndef CHAMPIONWRAPPER_H
#define CHAMPIONWRAPPER_H

#include "Champion.h"

using namespace std;

class ChampionWrapper
{
private:
	Champion* cham;
	
public:
	ChampionWrapper()					  
	{ 
		cham = 0;
	}
	ChampionWrapper(const string name)
	{
		cham = new Champion;
		cham->setName(name);
	}

	 ~ChampionWrapper()					   
	{ 
		 if (cham->getFreeOrNot())
			 delete cham;
		 else
			 cham = 0;
	}


	ChampionWrapper(const ChampionWrapper &right)  
	{	
			//cout << "CW copy constructor\n";
			cham = right.cham;
		
	}


	void setName(const string N)	   
	{
		if (!cham)
		{
			cham = new Champion;
			cham->setName(N);
		}
		else 
			cham->setName(N); }
	void setAbility(const string A[])      { cham->setAbility(A); }
	void setRole(const string R)           { cham->setRole(R); }
	void setType(const string T)           { cham->setType(T); }
	void setStats(const Stats C)           { cham->setStats(C); }
	void setChampion(const ChampionWrapper &Ch)	   { cham = Ch.getChampion(); }
	void setFree(){ cham->setFreeOrNot(true); }

	string  getName() const	               { return cham->getName(); }
	int 	nameCount() const 			   { return cham->getName().size();}
	string  getAbility(int n) const        { return cham->getAbility(n); }
	string  getRole() const                { return cham->getRole(); }
	string  getType() const                { return cham->getType(); }
	Stats   getStats() const               { return cham->getStats(); }
	Champion* getChampion() const		   { return cham; }

	bool operator < (const ChampionWrapper &right)
	{
		return this->getName() < right.getName();
	}
	bool operator > (const ChampionWrapper &right)
	{
		return (this->getName() > right.getName());
	}

	bool operator == (const ChampionWrapper &right)
	{
		return (this->getName() == right.getName());
	}

	void operator=( const ChampionWrapper &right)
	{
		this->cham = right.cham;
	}
};



#endif