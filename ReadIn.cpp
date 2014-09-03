//Created by Khoa Vo, modified by Takahiro Ishikawa

#include "Readin.h"

using namespace std;

// ouput the recent updated data in text format
void WriteOut(championDB& db)
{
	ChampionWrapper championOne;
	ofstream outFile;
	string *ptr;
	string file;
	Stats A, B;
	int count = 0;
	cout << "Enter the name of file you want to write(Press Enter to overwrite the default Riot.txt): ";
	getline(cin, file);
	if (file == "")
		outFile.open("Riot.txt");
	else
	{
		if (file.find(".txt") == -1)
			file = file + ".txt";
		outFile.open(file);
	}


	//cout << "Reaching before getRole...." << endl;
	//cout << "Reaching before getRole...." << endl;
	for (int i = 0; i < db.hashTable->getSize(); i++)			// loop through array
	{
		if (db.hashTable->getData(championOne, i))				// there is an elmeent in the i index
		{
			outFile << championOne.getName() << ",";			 
			B = championOne.getStats();							
	
				for (int k = 0; k < 5; k++)
				{
					outFile << championOne.getAbility(k);
					outFile << ",";
				}
				outFile << championOne.getRole() << ",";
				outFile << championOne.getType() << ",";
			outFile << B.attack << "," << B.defense << "," << B.abilityP << "," << B.difficulty ;
			count++;
			if (count < db.hashTable->getItemCount())			// no extra space at the end of the file
				outFile << endl;
		}
	}
	outFile.close();
	return;
}

void compare(championDB& db)
{
	string ans = "";
	do
	{
		list<ChampionWrapper> dataList;
		cout << "Please input the Champion names that you want to compare: " << endl;
		cout << "Champion 1: ";
		string champion1, champion2;
		getline(cin, champion1);
		Capitalize(champion1);
		cout << "Champion 2: ";
		getline(cin, champion2);
		Capitalize(champion2);
		ChampionWrapper championOne(champion1);
		ChampionWrapper championTwo(champion2);
		bool both, first, second, no = false;
		both = true;
		bool pass = false;
		do
		{
			// case 1: both name found in the hash table data (faster search than tree)
			if (db.hashTable->search(championOne) && db.hashTable->search(championTwo))
			{
				system("cls");
				dataList.clear();
				dataList.push_back(*(db.hashTable->search(championOne)));
				dataList.push_back(*(db.hashTable->search(championTwo)));
				for (list<ChampionWrapper>::iterator it = dataList.begin(); it != dataList.end(); ++it)
					Output(*it);
				pass = true;
			}
			// case 2: only data one found
			else if (db.hashTable->search(championOne))
			{
				system("cls");
				dataList.clear();
				cout << "Only " << championOne.getName() << " found." << endl;
				dataList.push_back(*(db.hashTable->search(championOne)));
				for (list<ChampionWrapper>::iterator it = dataList.begin(); it != dataList.end(); ++it)
					Output(*it);
				cout << "Would you want to continue to compare? (any key to continue, q for quit): ";
				getline(cin, ans);
				ans = toupper(ans[0]);
				if (ans == "Q" || ans == "q")
					return;
				else
				{
					cout << "The other champion name?: ";
					getline(cin, champion2);
					Capitalize(champion2);
					championTwo.setName(champion2);
				}
			}
			// case 3: only data two found
			else if (db.hashTable->search(championTwo)) // only champion 2 name found
			{
				system("cls");
				dataList.clear();
				cout << "Only " << championTwo.getName() << " found." << endl;
				dataList.push_back(*(db.hashTable->search(championTwo)));
				for (list<ChampionWrapper>::iterator it = dataList.begin(); it != dataList.end(); ++it)
					Output(*it);

				cout << "Would you want to continue to compare? (any key to continue, q to quit): ";
				getline(cin, ans);
				ans = toupper(ans[0]);
				if (ans == "Q" || ans =="q")
					return;
				else
				{
					cout << "The other champion name?: " << endl;
					getline(cin, champion1);
					Capitalize(champion1);
					championOne.setName(champion1);
				}
			}
			// case 4: both does not found
			else
			{
				cout << "Both of the input is not in the data base " << endl;
				cout << "Would you want to continue to compare? (any key to continue, q to quit): ";
				getline(cin, ans);
				ans = toupper(ans[0]);
				if (ans == "Q" || ans == "q")
					return;
				else
				{
					cout << "Champion 1: ";
					getline(cin, champion1);
					Capitalize(champion1);
					championOne.setName(champion1);
					cout << "Champion 2: ";
					getline(cin, champion2);
					Capitalize(champion2);
					championTwo.setName(champion2);
				}	
			}
		}while(!pass);
		
		pass = false; // reset the pass command

		// Part 2
		// - Loop until the user choose quit
		// - Prompt to receive key and position to insert
		// - Receive input for the key and position
		// - Check key with hashing function in hashtable
		// - If found, update it to list at the location and display
		// - End loop
	
		cout << "You want further comparison? " << "\nEnter q to quit: " << "\nPress Enter to continue: ";

		getline(cin, ans);
		ans = toupper(ans[0]);
		if (ans == "Q" || ans == "q")
			return;
					
		string champion3;
		Champion championThree;
		string position;
		int i_position;
		bool found = true;
		do
		{
			cout << "Champion Name?: ";
			getline(cin, champion3);
			Capitalize(champion3);
			ChampionWrapper championThree(champion3);
			bool pass;
			do
			{
				cout << "Where do you want to insert it?: ";
				getline(cin, position);
				
				if (((atoi(position.c_str())) > (dataList.size()) || (atoi(position.c_str()))<1))
				{
					if (dataList.size() >= 4)
						cout << "The input is invalid. Please input the number from 1 to 4" << endl;
					else
						cout << "The input is invalid. Please input the number from 1 to " << dataList.size() + 1 << endl;
				}
			} while ((atoi(position.c_str()))>(dataList.size() + 1) || (atoi(position.c_str())) < 1 || (atoi(position.c_str()))==5);
			i_position = atoi(position.c_str());
			if (db.hashTable->search(championThree))
			{
				system("cls");
				cout << "Inserted " << endl;
				list<ChampionWrapper>::iterator it = dataList.begin();
				if (dataList.size()==4)
					dataList.pop_back();
				for (int i = 0; i < i_position-1;i++)
					it++;;
				dataList.insert(it, *(db.hashTable->search(championThree)));
				cout << "The List " << endl;
				for (list<ChampionWrapper>::iterator it = dataList.begin(); it != dataList.end(); ++it)
					//it->displayData();
					Output(*it);
				cout << "Continue? (any key to continue, q to quit): "; // error happend when a string with space like "Quantum Computer";
				getline(cin, ans);
				ans = ans[0];
			}
			else
			{
				cout << "The Champion was not found." << endl;
				cout << "Continue? (Press enter key to continue, q to quit): ";
				getline(cin, ans);
				ans = toupper(ans[0]);
			}
		}while(ans!="Q" && ans != "q");
		cout << "You wanna starting over? (any key to continue; q to quit): ";
		getline(cin, ans);
		dataList.clear();
		ans = ans[0];
		if (ans == "q" || ans == "Q")
			return;
	}while(true);
	
}

// add an user input item in the both of hashed table and tree for shared adress of the object
bool addItem(championDB& db, ChampionWrapper& champ)
{
	if (!(db.hashTable->search(champ)))
	{
		db.championListTree->insert(champ);
		db.hashTable->addEntry(champ);
		system("cls");
		cout << "Following champion added: " << endl;
		Output(champ);
		return true;
	}
	cout << "The Item already exist in the data base." << endl;
	return false;
}

// delete the object that has same key with the user input
// ???? Why we should search by hashTable first?
// -> beacause it has faster serach on object and make sure that the deletion success
bool deleteItem(championDB& db, ChampionWrapper champ)
{
	cout << endl << endl;
	if (db.hashTable->search(champ))						// confirm the data same with user input 
															// key in the talbe with faster search in it
	{
		ChampionWrapper *temp;
		cout << "Following Data Deleted: " << endl;
		//champ.displayData();
		//(*(db.hashTable->search(champ))).displayData();
		temp = db.hashTable->search(champ);
		Output(*temp);
		db.hashTable->deleteEntry(champ);					// delete in the hash Table
		db.championListTree->remove(champ);					// this free the memoery of the object
		return true;
	}
	else
	{
		cout << "Deletion Failed" << endl;
		return false;
	}
}

// display the menu of filer search
void DisplayMenu_Filter()
{
	cout << "Filter:" << endl;
	cout << "'T' : Search for Type" << endl;
	cout << "'R' : Search for Role" << endl;
	cout << "Enter your choice here: ";
}

int CorrectNumber(string temp, int acceptedRange, int high, int restrictNum)
{
	int num = -8;
	int low = 1;
	int scoopyDoo;
	num = atoi(temp.c_str());
	while ((scoopyDoo = validInputType(temp, acceptedRange, high, restrictNum)) != 1){
		//num = atoi(temp.c_str());

		if (scoopyDoo == -4)
		{
			cout << "Please do not choose the same as the previous one: ";
			getline(cin, temp);
		}
		if (num == -1)
		{
			if (num == restrictNum)
				scoopyDoo = -3;
			else
				return -1;
		}

		if (scoopyDoo == -2){
			if ((num < 0 || num > high) && num != -1){
				cout << "Must be a number between " << low << " " << high << " \nEnter the number again: ";
				getline(cin, temp);
			}
			else{
				cout << "Must be a number: ";
				getline(cin, temp);
			}
		}

		if (scoopyDoo == -3)
		{
			cout << "Must be a number between " << low << " "<< high << " \nEnter the number again: ";
			getline(cin, temp);
		}

		num = atoi(temp.c_str());
	} 
	
	return num;
}



void removeSpace(string &str)
{
	while (str.length() != 0 && str.front() == ' ')
		str.erase(0, 1);

	while (str.length() != 0 && str.back() == ' ')
		str.erase(str.length() - 1, str.length());
}

/*
	return:
	1 true
	-2 
	-3
	-4
*/
int validInputType(string &str, int acceptedRange, int max, int restrictNum)
{
	removeSpace(str);
	if (str.length() == 0){
		return -2;
	}
	if (str.length() > acceptedRange){
		return -2;
	}
	for (int i = 0; i < str.length(); i++)
	{
	if (!isdigit(str[i]))
		return -2;
	}

	int value = atoi(str.c_str());

	if (value == restrictNum)
		return -4;

	if (value == -1)
	{
		if (str.length() > acceptedRange + 1)
			return -2;
	}


	if ((value <= 0 || value > max) && value != -1)
		return -3;

	return 1;
}

// filtering search by role
bool filtering(championDB& db, vector<string>& stringType, vector<string>& stringRole)
{
	int numrole1 = -1, numrole2 = -1, numtype1 = -1, numtype2 = -1;
	string temp1, temp2;
	cout << "SEARCH FILTER" << endl;
	ChampionWrapper temp("temp"); 
	string role, type;
	string str = "";
	int acceptedRange_type = 0; 
	int acceptedRange_role = 0;

	str = to_string(stringType.size());
	acceptedRange_type = str.length();
	str = to_string(stringRole.size());
	acceptedRange_role = str.length();

	// Ask for Role
	// Ask for primary role
	cout << "Choose the primary role, -1 for NO ROLE" << endl;
	Display_StringRole(stringRole);
	temp1 = "";
	getline(cin, temp1);
	//cin >> temp1;
	//removeSpace(temp1);
	numrole1 = CorrectNumber(temp1, acceptedRange_role, stringRole.size(), -9201);
	if (numrole1 != -1)
	{
	numrole1--;
	// Ask for secondary role
	cout << "Choose the secondary role, -1 for NONE" << endl;
	Display_StringRole(stringRole);
	getline(cin, temp2);
	//cin >> temp2;
	numrole2 = CorrectNumber(temp2, acceptedRange_role, stringRole.size(), numrole1 + 1);
	if (numrole1+1 == -1 && numrole2 == -1)
		temp.setRole("");
	else if (numrole2 == -1)
		temp.setRole(stringRole[numrole1]);
	else
	{
		//numrole2 = CorrectNumber(temp2, 1, stringRole.size(), numrole1 + 1);
		if (numrole2 == -1)
			temp.setRole(stringRole[numrole1]);
		else
		{
		numrole2--;
		temp.setRole(stringRole[numrole1] + "/" + stringRole[numrole2]);
		}
	}
	}


	
	// Ask for Type
	// Ask for primary type
	cout << "Choose the primary type, -1 for NO TYPE" << endl;
	Display_StringType(stringType);
	//cin >> temp1;
	temp1 = "";
	getline(cin, temp1);
	numtype1 = CorrectNumber(temp1, acceptedRange_type, stringType.size(), -9241);
	if (numtype1 != -1)
	{
	numtype1--;
	// Ask for secondary type
	cout << "Choose the secondary type, -1 for NONE" << endl;
	Display_StringType(stringType);
	getline(cin,temp2);
	//cin >> numtype2;
	numtype2 = CorrectNumber(temp2, acceptedRange_type, stringType.size(), numtype1 + 1);
	if (numtype1 +1 == -1 && numtype2 == -1)
		temp.setType("");
	else if (numtype2 == -1)
		temp.setType(stringType[numtype1]);
	else
	{
		//numtype2 = CorrectNumber(temp2, 1, stringType.size(), numtype1 + 1);
		if (numtype2 == -1)
			temp.setType(stringType[numtype1]);
		else
		{
		numtype2--;
		temp.setType(stringType[numtype1] + "/" + stringType[numtype2]);
		}
	}
	}

	db.championListTree->filterSearch(temp);
	return true;
}

// searching by name
bool searching(championDB& db , ChampionWrapper& champ)
{
	ChampionWrapper* temp ;
	if (db.hashTable->search(champ))
	{
		cout << champ.getName() << " Found: " << endl;
		temp = db.hashTable->search(champ);
		Output(*temp);
		return true;
	}
	else
	{
		cout << champ.getName() << " NOT Found.." << endl;
		return false;
	}
}

// display the data in the structure
void display(championDB& db, char ord)
{
	// alphabetical order represenation of data set
	if (ord == 'A')
	{
		cout << "Alphabetical Order: " << endl;
		db.championListTree->print('A');
		cout << endl;
	}
	// reverse order represenation of data set
	if (ord == 'R')
	{
		cout << "Reverse Order: " << endl;
		db.championListTree->print('R');
		cout << endl;
	}
	// intended tree
	if (ord == 'I')
	{
		cout << "Indented Tree: " << endl;
		db.championListTree->print('I');
		cout << endl;
	}
	// hash table
	if (ord == 'H')
	{
		cout << "List of the hash table: " << endl;
		db.hashTable->seeTable();
		cout << endl;
	}
}

// show the main menu
void DisplayMenu()
{
	cout << "\t*      *****  *\n\t*      *   *  *\n"
		 << "\t*      *   *  *\n\t*****  *****  *****\n"
		 << "\t(League of Legends)\n\n";
	cout << "Please select one of the option below" << endl
		 << "'A' : Add new champion info" << endl
		 << "'C' : Compare champion info" << endl
		 << "'D' : Delete the champion info" << endl
		 << "'H' : Show hash table stats" << endl
		 << "'P' : Print all the champion name" << endl
		 << "'S' : Search for the champion info" << endl
		 << "'Q' : Quit the program" << endl
		 << "Enter your choice here: ";
}

// show the print menu
void DisplayMenu_Print()
{
	cout << "PRINT:" << endl;
	cout << "'A' : Print in alphabet order" << endl;
	cout << "'H' : Print in hash table" << endl;
	cout << "'I' : Print in indent tree order" << endl;
	cout << "'R' : Print in reverse order" << endl;
	cout << "'M' : Go back to Menu" << endl;
	cout << "Enter your choice here: ";/*
	cout << "'I' : Print in hash stats" << endl;*/
}

// show the search menu
void DisplayMenu_Search()
{
	cout << "SEARCH:" << endl;
	cout << "'F' : Search filter" << endl;
	cout << "'N' : Search for name" << endl;
	cout << "'M' : Go back to Menu" << endl;
	cout << "Enter your choice here: ";
}

// show the type list
void Display_StringType(vector<string>  StringType)
{
	for (int i = 0; i < StringType.size(); i++)
		cout << i +1 << " "<< StringType[i] << endl;
	cout << "Enter the number of type: " ;
}

// show the role list
void Display_StringRole(vector<string>  StringRole)
{
	for (int i = 0; i < StringRole.size(); i++)
		cout << i + 1 << " " << StringRole[i] << endl;
	cout << "Enter the number of role: " ;
}

void createChampion(championDB& db, vector<string> &stringType, vector<string> &stringRole)
{
	//ChampionWrapper temp;
	ChampionWrapper* temp = new ChampionWrapper();
	string name;
	string ability[5];
	bool found = false;
	system("cls");
	cout << "Enter the character name you want to create: ";
	getline(cin, name);
	Capitalize(name);
	temp->setName(name);
	// Call search function
	if (db.hashTable->search(*temp))
	{
		cout << "The champion of the name already exist." << endl;
		return;
	}

	string ans;
	do
	{
		cout << "Would you want to set additional information about the champion?(y or n)" << endl;
		getline(cin, ans);
		Capitalize(ans);
	} while(ans[0] != 'Y' && ans[0] != 'N');

	Stats A;
	string role, role1, role2, type, type1, type2;
	int num = 0,a = 0;
	if (ans[0] == 'Y')
	{
		do
		{
			cout << "Enter the new champion primary role without space: ";
			getline(cin, role1);
		}while (role1.find(' ') != -1);
		do
		{
			cout << "Enter the new champion secondary role without space(Enter if none): ";
			getline(cin, role2);
		} while (role2.find(' ') != -1);
		// add the role to temp champion object
		if (role2 == "")
		{
			Capitalize(role1);
			while (a < stringRole.size())
			{
				if (role1 == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
			{
				if (role1 != "")
				stringRole.push_back(role1);
			}
			cout << "Role: " << role1 << endl;
			temp->setRole(role1);
		}
		else
		{
			Capitalize(role1);
			Capitalize(role2);	
			found = false;
			while (a < stringRole.size())
			{
				if (type1 == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
				stringRole.push_back(role1);

			found = false;
			a = 0;
			while (a < stringRole.size())
			{
				if (role2 == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
				stringRole.push_back(role2);
			role = role1 + "/" + role2;
			cout << "Role: " << role << endl;
			temp->setRole(role);
		}

		do
		{
			cout << "Enter the new champion primary type without space: ";
			getline(cin, type1);
		} while (type1.find(' ') != -1);
		do
		{
			cout << "Enter the new champion secondary type without space(Enter if none): ";
			getline(cin, type2);
		} while (type2.find(' ') != -1);

		if (type2 == "")
		{
			Capitalize(type1);
			// Check for new type
			while (a < stringType.size())
			{
				if (type1 == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
			{
				if (type1 != "")
				stringType.push_back(type1);
			}
			cout << "Type: " << type1 << endl;
			temp->setType(type1);
		}
		else
		{
			Capitalize(type1);
			Capitalize(type2);
			found = false;
			
			// Check for new Type
			while (a < stringType.size())
			{
				if (type1 == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
				stringType.push_back(type1);

			found = false;
			a = 0;
			while (a < stringType.size())
			{
				if (type2 == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
				stringType.push_back(type2);

			type = type1 + "/" + type2;
			cout << "Type: " << type << endl;
			temp->setType(type);
		}
		
		cout << "Enter the passive: ";
		getline(cin, ability[0]);
		cout << "Enter the first ability [Q]: ";
		getline(cin, ability[1]);
		cout << "Enter the second ability [W]: ";
		getline(cin, ability[2]);
		cout << "Enter the third ability [E]: ";
		getline(cin, ability[3]);
		cout << "Enter the forth ability [R]: ";
		getline(cin, ability[4]);

		for (int i = 0; i < 5; i++)
			Capitalize(ability[i]);

		temp->setAbility(ability);
		
		string number;
		// prompt for Stats
		// ask for attack power
			cout << "Enter the attack power of new champion(1-10): ";
			getline(cin, number);
			A.attack = CorrectNumber(number, 2, 10, -1);

		// ask for defense power
			cout << "Enter the defense power of new champion(1-10): ";
			getline(cin, number);
			A.defense = CorrectNumber(number, 2, 10, -1);

		// ask for ability power
			cout << "Enter the ability power of new champion(1-10): ";
			getline(cin, number);
			A.abilityP  = CorrectNumber(number, 2, 10, -1);

		// ask for difficulty
			cout << "Enter the difficulty of new champion(1-10): ";
			getline(cin, number);
			A.difficulty= CorrectNumber(number, 2, 10, -1);
			
		temp->setStats(A);
	}
	else
	{
		cout << "Only name woudld be added." << endl;
		cin.ignore();
		string c;
		getline(cin,c); // tentative stopper
	}

	addItem(db, *temp);

}

// major menu controling system. Core unit.
void MenuController(championDB& champDB, ChampionWrapper& temp ,char& choice, char& order, char& srh, vector<string>& stringType, vector<string>& stringRole)
{
	do
	{
		string c;
		string name;
		do
		{
			system("cls");
			DisplayMenu();
			getline(cin,c);
			choice = toupper(c[0]);
		}
		while (c.length() != 1 || (choice != 'P' && choice != 'S' && choice != 'A' && choice != 'D' &&  choice != 'C' &&  choice != 'H' && choice != 'Q'));

		if (choice == 'P')
		{
			do
			{
				system("cls");
				DisplayMenu_Print();
				getline(cin, c);
				order = toupper(c[0]);
			} 
			while (c.length() != 1 || (order != 'A' && order != 'I' && order != 'R' && order != 'H' && order != 'M'));
			if (order == 'M');
			
			else
			{
				//cout << "Before display:" << endl;
				display(champDB, order);
				cout << "Press Enter to continue...";
				getline(cin, c);	// tentative stopper
			}			
		}

		// search
		if (choice == 'S')
		{
			do
			{
				system("cls");
				DisplayMenu_Search();
				getline(cin, c);
				srh = toupper(c[0]);
			} while (c.length() != 1 || (srh != 'N' && srh != 'F' && srh != 'M'));

			// search by name
			if (srh == 'N')
			{
				system("cls");
				cout << "SEARCH NAME" << endl;
				cout << "Please enter the name: ";
				getline(cin, name);
				Capitalize(name);
				temp.setName(name);
				searching(champDB, temp);
				cout << "Press Enter to continue...";
				getline(cin,c); 							// tentative stopper
			}
			// search by filter
			if (srh == 'F')
			{
				system("cls");
				filtering(champDB, stringType, stringRole);
				cout << endl ;	
				cout << "Press Enter to continue...";
				getline(cin,c); // tentative stopper
			}
			if (srh == 'M');
		}

		// delete
		if (choice == 'D')
		{
			system("cls");
			cout << "Enter the character name you want to delete: ";
			getline(cin, name);
			Capitalize(name);
			temp.setName(name);
			deleteItem(champDB, temp);
			
			cout << "Press Enter to continue...";
			getline(cin,c); // tentative stopper
		}
		// update
		// add
		if (choice == 'A')
		{
			createChampion(champDB, stringType, stringRole);
			cout << "Press Enter to continue...";
			getline(cin, c); // tentative stopper
		}
		if (choice == 'C')
		{
			system("cls");
			compare(champDB);
			cout << "Press Enter to continue...";
			getline(cin,c); // tentative stopper
		}
		if (choice == 'H')
		{
			system("cls");
			champDB.hashTable->displayStats();
			cout << "Press Enter to continue...";
			getline(cin,c); // tentative stopper
		}
		if (choice == 'Q')
			return;
	}while(true);
}

// readin the txt file for producing the inital data structure with actual data
void ReadIn(championDB& db, vector<string> &stringType, vector<string> &stringRole)
{
	ifstream infile;
	string fname;
	int i = 0;
	string Abilities[5];
	string name, role;
	string type;
	Stats A, B;

	//infile.open("Riot.txt");
	cout << "Enter the file you want to open (Press Enter to open default file Riot.txt): ";
	getline(cin, fname);
	if (fname == "")
		infile.open("Riot.txt");
	else
	{
		if (fname.find(".txt") == -1)
			fname = fname + ".txt";
	infile.open(fname.c_str());
	}


	while (!infile)  // check for file open success or prompt for filename
	{
		cout << "Error opening Champions file\nEnter filename: ";
		cin >> fname;
		infile.open(fname.c_str());
	}


	// until the end of the line of the txt file
	while (!infile.eof())
	{
		ChampionWrapper* champ = new ChampionWrapper();

		// data retrieving one by one with spliter ','
		getline(infile, name, ',');
		getline(infile, Abilities[0], ',');
		getline(infile, Abilities[1], ',');
		getline(infile, Abilities[2], ',');
		getline(infile, Abilities[3], ',');
		getline(infile, Abilities[4], ',');
		getline(infile, role, ',');
		getline(infile, type, ','); // , , data base
		infile >> A.attack ;
		infile.ignore(10,',');
		infile >> A.defense ;
		infile.ignore(10,',');
		infile >> A.abilityP;
		infile.ignore(10,',');
		infile >> A.difficulty;
		infile.ignore(10,'\n');


		// set each retrieved data in the object
		champ->setName(name);
		champ->setAbility(Abilities);
		champ->setRole(role);
		champ->setType(type);
		//champ->setType(types);
		champ->setStats(A);

		// insert into the both of data strucutre as same adress
		db.championListTree->insert(*champ);
		db.hashTable->addEntry(*champ);

		// Getting StringType (All types are in the text)
		int a = 0;
		string *arr = new string[2];
		bool found = false, space = false;

		if (type.find('/') != -1)
		{
			arr = parse(type);
			found = false;
			
			while (a < stringType.size())
			{
				if (arr[0] == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
			{
				stringType.push_back(arr[0]);
			}
				

			found = false;
			a = 0;
			while (a < stringType.size())
			{
				if (arr[1] == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
				stringType.push_back(arr[1]);
		}
		else
		{
			found = false;
			while (a < stringType.size())
			{
				if (type == stringType[a])
					found = true;
				a++;
			}
			if (found == false)
				stringType.push_back(type);			
		}


		// Getting StringRole (All Roles are in the text)
		a = 0;
		found = false, space = false;


		if (role.find('/') != -1)
		{
			arr = parse(role);
			found = false;

			while (a < stringRole.size())
			{
				if (arr[0] == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
			{
				stringRole.push_back(arr[0]);
			}


			found = false;
			a = 0;
			while (a < stringRole.size())
			{
				if (arr[1] == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
				stringRole.push_back(arr[1]);
		}
		else
		{
			found = false;
			while (a < stringRole.size())
			{
				if (role == stringRole[a])
					found = true;
				a++;
			}
			if (found == false)
				stringRole.push_back(role);
		}        
	}
	return;
}

// Capitalize the letter for usre input confirmation (capital and non-capital input acceptable)
void Capitalize(string &something)
{
	int i = 0;
	removeSpace(something);
	while (i < something.size())
	{
		something[i] = tolower(something[i]);
		if (something[i] == ' ')
		{
			something[i + 1] = toupper(something[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	something[0] = toupper(something[0]);

}

// parse the strings (type and role) for data input and output process
string* parse(string type)
{
	int loc = 0;
	string *arr = new string[2];
	loc = type.find('/');
	if (loc != -1)
	{
	arr[0] = type.substr(0, loc);
	arr[1] = type.substr(loc+1);
	}
	else
	{
		arr[0] = type;
	}

	return arr;
}

void Output(ChampionWrapper& champ)
{

	Stats B;
	HANDLE  hConsole;
	int k;
	string skill[5] = { "Passive", "Q", "W", "E", "R" };

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	B = champ.getStats();
	cout << endl;
	cout << champ.getName() << endl;
	for (int k = 0; k < 5; k++)
	{
		cout << "[";
		SetConsoleTextAttribute(hConsole, 14);
		cout << skill[k];
		SetConsoleTextAttribute(hConsole, 7);
		cout << "]  ";
		cout << champ.getAbility(k) << endl;
	}
	cout << endl;
	cout << left << setw(8) << "Role: " << left<< setw(15) << champ.getRole() << endl;
	cout << left << setw(8)<< "Type: " << left << setw(15) << champ.getType() << endl;
	cout << endl;
	//cout << B.attack << "  " << B.defense << "  " << B.abilityP << "  " << B.difficulty << endl;

	Display_Stats("Attack power", 201, B.attack);
	Display_Stats("Defense power", 33, B.defense);
	Display_Stats("Ability power", 145, B.abilityP);
	Display_Stats("Difficulty", 81, B.difficulty);
	cout << "*********************************************************************" << endl;

}

void Display_Stats(string name, int color, int stat)
{
	HANDLE  hConsole;
	int k;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << left << setw(20) << name << " ";
	SetConsoleTextAttribute(hConsole, color);
	for (k = 0; k < 2 * stat; k++)
		cout << " ";

	SetConsoleTextAttribute(hConsole, 130);
	for (k = 0; k < 2 * (10 - stat); k++)
		cout << " ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl;

}

//Ezreal,Rising Spell Force,Mystic Shot,Essence Flux,Arcane Shift,Trueshot Barrage,Bottom,Mid,Marksman/Mage,7,2,6,8
/*
	add
		prompt user the key
		seach for dupicate and back out
		if not dupicate:
			prompt for the rest of data fields
			add as above
	delete
		prompt user for key
		search for existing data or backout
		delete and look for bollean return value
			-either hash or BST deleting the data
			- or hash or BST returning the delted data, to be deleted
			- or goes to undo if you have this option
	printHash
	printInorder
	printIndentedTree
	quit
		save:
			prompt the user for output file
			walk the has
			or, if you have breadthFirst, then use breadthFirst
			save in the same format as input file
		delete all memory
		end
*/