//Created by Khoa Vo
#ifndef READIN_H
#define READIN_H

//#define SMALL 30
#include <windows.h>
#include "HASH.h"
#include "ChampionWrapper.h"
#include "ChampionListTree.h"
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct championDB
{
	int count;
	int arrSize;
	ChampionListTree *championListTree = new ChampionListTree();
	HASH *hashTable = new HASH();
};

// modeling: 
// : read data from a text file line by line into the hash and tree data strucuture 
void ReadIn(championDB& db, vector<string> &, vector<string> &);
// : capitalize the first char of user input string
void Capitalize(string &something);
// : parse the user input on the type and role for related data manipulation
string* parse(string type);
// : write out the latest version of the data set into a txt file
void WriteOut(championDB& db);
// : Output all the data in the champion object
void Output(ChampionWrapper& champ);
// : Output color for the Stats
void Display_Stats(string name, int color, int stat);
// : Check for number, and display the errors
int CorrectNumber(string temp, int acceptedRange, int high, int restrictNum);
// : Remove all extra the space in front and after 
void removeSpace(string &);
// : Check what errors for the input, and return a number for that number
int validInputType(string &str, int acceptedRange, int max, int restrictNum);

// process:
// : create champion object for adding it in the data base
void createChampion(championDB& db, vector<string> &stringType, vector<string> &stringRole);
// : add an item 
bool addItem(championDB& db, ChampionWrapper& champ);
// : delete an item
bool deleteItem(championDB& db, ChampionWrapper champ);
// : search an item
bool searching(championDB& db , ChampionWrapper& champ);
// : filteering search for the data base
bool filtering(championDB& db, vector<string>& stringType, vector<string>& stringRole);
// : compare the max four data
void compare(championDB& db);

// userinteraction:
// : display the data in choice of order 
void display(championDB& db, char ord);
// : display the main menu
void DisplayMenu();
// : disply the choice (Alphabetical, Reverse, Indented Tree, Hahs Table) in the print manu in the main menu
void DisplayMenu_Print();
// : display menu for the search (by name or filter)
void DisplayMenu_Search();
//void DisplayMenu_Filter();
void DisplayMenu_SearchFilter(vector<string> );
// : display the string type in the data set for user option
void Display_StringType(vector<string>  StringType);
// : dislat the string role in the data set for user option
void Display_StringRole(vector<string>  StringRole);
// : user interaction for controlling the all of user accessable features
void MenuController(championDB& champDB, ChampionWrapper& temp ,char& choice, char& order, char& search, vector<string>& stringType, vector<string>& stringRole);
// : display the hash stats of the data set
void Display_Stats(string, int, int);

#endif