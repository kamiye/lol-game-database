/*
 Implementation of ChampionListTree.h
 By Ye Aung
 */

#include "ChampionListTree.h"

/************** Independent functions that will be passed down in the argument *******************/
void _setFree(ChampionWrapper *anItem)
{
	anItem->setFree();
}

void displayListData(ChampionWrapper &anItem)
{
	cout << left << setw(20) << anItem.getName() << setw(23) << left << anItem.getRole() 
		 << left << setw(23) << anItem.getType() << endl;
}

void indentDisplay(ChampionWrapper &anItem, int h)
{
	for (int i = 0; i < (h - 1); i++)
		cout << '\t';
	cout << '[' << h << ']' << anItem.getName() << endl;
}

// figured out... formatting issues.
void filterDisplayRole(ChampionWrapper &current, ChampionWrapper &target, int &num)
{

	if ((((current.getRole()).find(target.getRole()) < current.getRole().length() && (current.getRole()).find(target.getRole()) != -1) || target.getRole() == "") &&
		((current.getType()).find(target.getType()) < current.getRole().length() && (current.getType()).find(target.getType()) != -1 || target.getType() == ""))
	{
		cout << left << setw(20) << current.getName() << setw(23) << left << current.getRole()
			<< current.getType() << endl; num++;
	}
}
/*********************************************************************************************/

//Print the whole data in the tree alphabetical or reverse alphabetical or indented tree
void ChampionListTree::print(const char choice) const
{
	if (!championTree->isEmpty())
	{
		cout << "Total: " << championTree->size() << endl;
		if (toupper(choice) == 'A' || toupper(choice) == 'R')
		{
			cout << endl << left << setw(20) << "Name" << setw(23) << left << "Role"
				 << left << setw(23) << "Type" << endl << endl;
			if (toupper(choice) == 'A')
			{
				championTree->inOrder(displayListData);
			}
			else if (toupper(choice) == 'R')
			{
				championTree->reverseOrder(displayListData);
			}
		}
		else if (toupper(choice) == 'I')
			championTree->indentTree(indentDisplay);
	}
	else
	{
		cout << "Tree is Empty!" << endl;
	}
}

//Print out the data in the tree that contains the category(Role and Type) that user wants
//EX: Top and Tank, Top only, Mid and Assassin, Assassin only etc.
void ChampionListTree::filterSearch( ChampionWrapper &filtered) const
{
	int numFound = 0;
	championTree->filterOrder(filterDisplayRole, filtered, numFound);
	if (numFound == 0)
		cout << "\nFilter Search Not Found!\n";
}

//Walk the whole tree to set the condiiton of destructor to true
void ChampionListTree::setFree()
{
	championTree->freeMe(_setFree);
}