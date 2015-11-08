#include "Hash_Table.h"
#include <math.h>

// constructor
hash_Table::hash_Table(int size)
{
	vector<word> table(size);
	makeEmpty();
}

// insert - modified from book
void hash_Table::insert(char * string)
{
	// send to hash function
	unsigned int pos = hash(string);

	// see if it is already in the table
	unsigned int found = find_Pos(string);
	if (table[found].info == ACTIVE)
		table[found].frequency++;

	else
	{
		table[pos].set_Item(string);
		table[pos].frequency = 1;
		table[pos].info = ACTIVE;
		numElements++;
	}

	//check lambda value
	float lambda = get_Lambda();

	// if too high, rehash the table, else return from function
	if (lambda >= 0.75)
	{
		rehash();
		return;
	}

	else
		return;
}

// find - modified from book
// Needs work
unsigned int hash_Table::find_Pos(char * string)
{
	//get hash value and start traversal there
	unsigned int pos = hash(string);
	
	// traverse vector "table" and see if the current entry is 
		// not deleted and has the same char * string as the one we're trying to find
	//this loop will drop out once it reaches an empty position (will not go forever!)
	while (table[pos].info != EMPTY && table[pos].get_Item() != string)
	{
		pos ++;				//using linear probing
		if (pos >= tableSize)
			pos -= tableSize;
	}

	return pos;
}

// delete - modified from book
	// get hash value
	// traverse vector "Table" until you find the item
	// mark the item .info as EMPTY
void hash_Table::remove (char * string)
{	
	int pos = hash(string);
	if (table[pos].info == ACTIVE)
		table[pos].info = DELETED;

}

// hash function (direct from book, with speed modifications learned in CSC314)
unsigned int hash_Table::hash(char * word)
{
	unsigned int hashVal = 0;
	for (unsigned int i = 0; i < sizeof(word); i ++)
	{
	// Original book code: hashVal = 37 * hashVal + ch;

	// as per what we've learned in assembly, multiplication takes way longer than shift/add operations.
	// If we're doing an entire book of words, those extra clock cycles could really add up.
	hashVal = (hashVal << 5) + (hashVal << 2) + hashVal + word[i];
	}
	
	return hashVal % tableSize;
}

void hash_Table::rehash()
{
	cout << "Rehashing...Load factor (lambda) is: " << lambda << ". " << endl;

	vector<word> oldTable = table;
	
	table.resize(get_nextPrime( 2 * get_tableSize()));
	for (unsigned int i = 0; i < tableSize; i++)		//for each thing in the table, set to empty
		table[i].info = EMPTY;

	numElements = 0;

	for (unsigned int i = 0; i < tableSize; i++)
	{
		if (table[i].info == ACTIVE)
		{
			insert( std:: move (table[i].get_Item()) ) ;
			numElements++;
		}
	}

	// delete oldTable; <---- is this safe?
	cout << "Rehash complete." << endl;
}

// get next prime number after the one you input for rehashing the table
// Needs work with for-loop
int hash_Table::get_nextPrime(int num)
{
	bool prime;	

	//add one to the number passed in until you find a prime number
	for (int i = num; i < num * 2; i++)
	{
		prime = isPrime(num);
		if (prime)
			return i;
	}

	return 0;					// <--- this would be an error...
}

//Function for checking whether a number is prime
bool hash_Table::isPrime(int num)
{
	if (num <= 1)
		return false;

	if (num == 2 || num == 3)
		return true;

	for (int i = 0; i < sqrt(num) + 1; i++)
	{
		if ( num % i == 0)
			return false;
	}

	return true;
} 

//Make each entry in the hash table read as EMPTY
void hash_Table::makeEmpty()
{
	for (auto & entry: table)
		entry.info = EMPTY;
}

//get lambda
float hash_Table::get_Lambda() const
{
	return float(numElements/tableSize);
}

//get table size
unsigned int hash_Table::get_tableSize() const
{
	return tableSize;
}

// get numElements
unsigned int hash_Table::get_numElements() const
{
	return numElements;
}


