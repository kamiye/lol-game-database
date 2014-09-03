// Hashed Table class header file
// Name: Dennis Xing
// Date: 5/23/2014


#ifndef _HASH
#define _HASH

#include "ChampionWrapper.h"
#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <stack>

// MAX_SIZE 53 because.. 
// 1. Prime
// 2. Load Factor 50-75% for the number of initial data (27)
int const MAX_SIZE = 53;

struct ELEMENT
{
	ChampionWrapper* champ; 
	int probes; 											// -1: empty state, -2: deleted state, 0: no probe but have 1 el, n: n probes
	ELEMENT() 											   { champ = 0; probes = -1; }
};

class HASH
{
private:
	// : hash array with the ELEMENT struct
	ELEMENT hashTable[MAX_SIZE];				
	// : number of the data in the table
	int itemCount;											
	// : itemCount / MAX_SIZE
	int loadFactor;
	// calculation of the load factor for the display stats
	// Calculation : (# of data / MAX_SIZE (hash table))											
	double calcLoadFactor();
	// CHECK : producing 2..5 home adresses having probe(s)
	int getHashIndex(ChampionWrapper & c) const;
	// Reason of choice: Simple and manageable for small data set
	int collisionLinearResolution(const int i) const; 
	// linear collision resolution in inverse way
	int inverseLinearResolution(int i);
	void collisionPath(int index, int step);
	// check if the table is available to be added data into
	bool overCapacity();

public: 
	// constructor:
	// : defalt constructor	
	HASH();													// default constructor
	
	// accesssor:
	int getSize() const										{ return MAX_SIZE;  };
	int getItemCount() const 								{ return itemCount; };

	// process/script:
	// : add a data in a index which was hashed and even collision resolusioned
	bool addEntry(ChampionWrapper & c);
	// : delete for user input key
	bool deleteEntry(ChampionWrapper & c);
	// : dispaly the stats of the hash
	void displayStats();
	// : seach an element in the search function
	ChampionWrapper* search(ChampionWrapper & c) const;
	// : see the every indexes of the hash table
	void seeTable();
	// : update an element in the hash table
	bool update(ChampionWrapper & c);
	// : extract existing data in the hash table
	bool getData(ChampionWrapper & c, int i);
};

#endif 