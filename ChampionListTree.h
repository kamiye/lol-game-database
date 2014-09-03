#ifndef CHAMPION_LIST_TREE_H
#define CHAMPION_LIST_TREE_H

#include "BinarySearchTree.h"
#include "Champion.h"
#include <iostream>
#include <iomanip>
#include <string>
#include"ChampionWrapper.h"
using namespace std;

class ChampionListTree
{
private:
	BinarySearchTree<ChampionWrapper> *championTree;
public:
	ChampionListTree()									{ championTree = new BinarySearchTree<ChampionWrapper>; };
	int getSize() const 								{ return championTree->size(); };
	bool insert(const ChampionWrapper & target) 		{ return championTree->insert(target); };
	bool remove(const ChampionWrapper & target) 		{ return championTree->remove(target); };
	void print(const char) const;
	void filterSearch( ChampionWrapper &filtered) const;
	void setFree(); 
};

#endif