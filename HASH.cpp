// Hashed Table class implementation file
// Name: Created by Dennis Xing, Modified by Takahiro Ishikawa
// Date: 5/23/2014

#include "HASH.h"

using namespace std; 

// default constrcutor 
HASH::HASH()
{ 
	for (int i = 0; i < MAX_SIZE; i++)
	{
		hashTable[i].champ = 0;
	}
	itemCount = 0;
	loadFactor = 0;
}

// check if the table is available to be added data into
bool HASH::overCapacity()
{
	if (itemCount>=MAX_SIZE)
	{
		cout << "Hash Table : Over Capacity" << endl;
		return true;
	}
	else 
		return false;
}

// make a hash index
// CHECK : producing 2..5 home adresses having probe(s)
int HASH::getHashIndex(ChampionWrapper & c) const
{
	long long sum = 0;
	for (int i = 0; i < c.nameCount(); i++)						// string parsing
		sum = sum + (c.getName()[i] * 3); 						// askii value sums
	return sum % MAX_SIZE;										// the sum's module
}


/*========= Collision resolution: Linear ======== */
// Reason of choice: Simple and manageable for small data set
int HASH::collisionLinearResolution(int i) const
{
	i = i+1;
	if (i >= MAX_SIZE)
		i = i % MAX_SIZE;
	return i;
}

// linear collision resolution in inverse way
int HASH::inverseLinearResolution(int i)
{
	i = i-1;
	if (i <= -1)
		i = i + MAX_SIZE;
	return i;
}

// add a data in a index which was hashed and even collision resolusioned
bool HASH::addEntry(ChampionWrapper & c) 
{
	if (overCapacity())											// check availability of the space
		return false;
	int i = getHashIndex(c);									// get the hash value
	if (hashTable[i].probes <= -1)								// if the hash talble is empty or deleted
	{	
		hashTable[i].champ = &c;								// set the element in the hashtable
		if (hashTable[i].probes == -2)
			hashTable[i].probes = 0;
		else
			hashTable[i].probes = 0;
		itemCount++;											// increment the item count
		return true;
	}
	int probes = 0;												// for comapring with the item count
	while ( hashTable[i].probes >= 0  && probes < itemCount)	// colilsion and outof bound case
	{ 
		i = collisionLinearResolution(i);								// linear resolution
		probes++;
		if (hashTable[i].probes <= -1)							// if the hash talble is empty or deleted
		{	
			hashTable[i].champ = &c;							// set the element in the hashtable
			if (hashTable[i].probes == -2)
				hashTable[i].probes = 0;
			else
				hashTable[i].probes = probes;					// put the probes' count
			itemCount++;										// increment the item count
			return true;
		}
	}
	return false; 
}

// delete for user input key
bool HASH::deleteEntry(ChampionWrapper & c)
{
	int i = getHashIndex(c);									// hashing the search key
	if (hashTable[i].probes>=0 && *hashTable[i].champ == c)		// match case with initial hashed key
	{
		hashTable[i].champ = 0;									// set the champ null
		hashTable[i].probes = -2;								// change status into "deleted(-2)"
		itemCount--;											// change the item count
		return true;											// deleted
	}
	else
	{
		int counter = 0;
		while (hashTable[i].probes!=-1 && counter < itemCount)	// not match with inital hashed key
		{ 
			counter++;
			i = collisionLinearResolution(i);							// Linear
			if (hashTable[i].probes>=0)							// there is more than one element
			{
				if (*hashTable[i].champ == c)					// the el match with the user input
				{
					hashTable[i].champ = 0;						// set the champ null
					hashTable[i].probes = -2;					// change the status into "deleted(-2)"
					itemCount--;								// change the item count
					return true;								// deleted
				}
			}
		}
	}
	return false;												// not deleted (not match keys)
}

// calculation of the load factor for the display stats
// Calculation : (# of data / MAX_SIZE (hash table))
double HASH::calcLoadFactor()
{
	int dataInElement = 0;
	double load;
	for(int i = 0; i < MAX_SIZE; i++)
	{
		if(hashTable[i].probes>=0)
			dataInElement++;
	}
	load = static_cast<double>(dataInElement) / MAX_SIZE * 100.0;
	return load;
}

// trackign down the collison path of a probe
void HASH::collisionPath(int index, int step)
{
	stack<int> sIndex;
	sIndex.push(index);											// push the inital elmeent(the deepest element)
	for (int j = 0; j < step; j++)
	{
		index = inverseLinearResolution(index);                 // inversely track up the index
		sIndex.push(index);										// add index every track up
	}
	int path = 0;
	while (!sIndex.empty())										// display collision path from starting index to the deepest index
	{
		if (hashTable[sIndex.top()].probes != -2)
		{
			cout << "Index: " << sIndex.top() << "  " << hashTable[sIndex.top()].champ->getName() << endl;
			sIndex.pop();
		}
		else
		{
			cout << "Index: " << sIndex.top() << endl;
			sIndex.pop();
		}
	}
}	


// display the hash table statistics
void HASH::displayStats()
{
	loadFactor = calcLoadFactor();								
	int highestProbe = 0,collision = 0;
	// noCollision = 0, 
    cout << setprecision(2) << fixed; 
    cout << "There are " << itemCount << " words in the database" << endl 
         << "The size of the database is " << MAX_SIZE << endl 
         << "Load factor is " << loadFactor << '%' << endl << endl << "Collisions :\n\n"; 

    for (int i = 0; i < MAX_SIZE; i++) 
    { 
    	if (hashTable[i].probes >=1)
    	{
       		cout << "at " << i << " " << hashTable[i].champ->getName() << endl;
       		collision++;
       	}
        if(hashTable[i].probes >= 0) 
        {
            if (hashTable[i].probes > highestProbe)
                highestProbe = hashTable[i].probes;
        } 
        //else if(hashTable[i].probes!=0)
        //    noCollision++;
    }

    cout << "Number of collisions: " << collision << endl;
  
    cout << "\nMax number of probes is " << highestProbe << " at:" << endl; 
    for(int i = 0; i < MAX_SIZE; i++) 
    { 
        if((hashTable[i].probes) == highestProbe)
        { 
            collisionPath(i, highestProbe);
        } 
    } 
}

// seach an element in the search function
ChampionWrapper* HASH::search(ChampionWrapper & c) const
{
	int i = getHashIndex(c);									// hashing the search key
	if (hashTable[i].probes>=0 && *hashTable[i].champ == c)		// match with initial hashed index
		return hashTable[i].champ;								// return the key found
	else
	{
		int counter = 0;
		while (hashTable[i].probes!=-1 && counter < itemCount)	// not match with initial hashed index
		{ 
			counter++;
			i = collisionLinearResolution(i);					// Linear collision resol
			if (hashTable[i].probes>=0)							// there is an data
			{
				if (*hashTable[i].champ == c)					// the data match with user input key
					return hashTable[i].champ;					// return the key
			}
		}
	}
	return 0;													// return null if not found
}

// see the every indexes of the hash table
void HASH::seeTable()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		cout << "index: " << i << "  ";
		cout << "Probes: " << hashTable[i].probes << "  ";
		if (hashTable[i].probes>=0)
			cout << "Name: " << hashTable[i].champ->getName() << endl;
		else
			cout << endl;
	}
}

// update an element in the hash table
bool HASH::update(ChampionWrapper & c)
{
	if(!(this->search(c)))
	{
		this->addEntry(c);
		delete (this->search(c));
		return true;
	}
	else
		return false;
}

// extract existing data in the hash table
bool HASH::getData(ChampionWrapper & c, int i)
{
	if (hashTable[i].probes >= 0)
	{
		c = *hashTable[i].champ;
		return true;
	}
	else 
		return false;
}