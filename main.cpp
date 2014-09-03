// insertion
// deletion
// search
// display
// - intended
// - alphabeticla
// compares

/* Develpoment Plan
1. Making the buiding fucntion with the io stream and bst
2. bst code implementation on the insertion, deletion, display.
3. hash implementation
4. compare implementation
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "ChampionListTree.h"
#include "ChampionWrapper.h"
#include "ReadIn.h"

using namespace std;

void start()
{

	// readin: success
	championDB champDB;												// create the championDB instance
	vector<string> types, roles;
	ReadIn(champDB, types, roles);									// ReadIn: txt data

	// menu controling
	ChampionWrapper tempChamp("temp"); 								// should I always dinamically alocate?
	char choice, order, search;
	MenuController(champDB, tempChamp, choice, order, search, types, roles);
	WriteOut(champDB);
	champDB.championListTree->setFree();
	return;
}

// diplsay the alphabetical, reverse and indented tree
int main()
{
	start(); // Start the game!!!
	return 0;
}

