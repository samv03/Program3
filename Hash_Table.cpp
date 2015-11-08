#include "Hash_Table.h"

// constructor
hash_Table::hash_Table(int size);
{
	vector<word> table(size);
	makeEmpty();
}

//default destructor
hash_Table::~hash_Table();

// insert
void hash_Table::insert(char * string)
{
	// send to hash function
	unsigned int pos = hash(string);

	// see if it is already in the table
	bool found = find(string);
	if (found)
		table[pos].
		// if it is, increment the frequency of the word

	// otherwise, add to table 
		//find position and insert
}
	

// find
bool hash_Table::find(char * string)
{
	//get hash value and start traversal there
	// traverse vector "table" and see if the current entry is 
		// not deleted and has the same char * string as the one we're trying to find
	// if found, return true;
	// else, return false;

}


// delete
	// get hash value
	// traverse vector "Table" until you find the item
	// mark the item .info as EMPTY
void remove (char * string)
{	
	int pos = hash(string):
	if (table[pos].info == ACTIVE)
		table[pos].info = DELETED;

}

void makeEmpty();
{
	for (auto & entry: table)
		entry.info = EMPTY;
}

//get Lambda
float hash_Table::get_Lambda()
{
	return numElements/tableSize;
}

//get table size
int hash_Table::get_tableSize()
{
	return tableSize;
}

// get numElements
int hash_Table::get_num_Elements()
{
	return numElements;
}

// hash function (from book)
// Ideas on how to modify: shift bits left/right by primes?
unsigned int hash_Table::hash(char * word)
{
	unsigned int hashVal = 0;
	for (char ch : word)
	{
	hashVal = 37 * hashVal + ch;
	}
	
	return hashVal % tableSize;
}

// get next prime number after the one you input for rehashing the table
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

	return 0;			// <--- this would be an error...
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
