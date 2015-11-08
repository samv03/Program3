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
	// see if it is already in the table
		// if it is, increment the frequency of the world

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
void remove (char * string)
{
	// get hash value
	// traverse vector "Table" until you find the item
	// mark the item .info as EMPTY
	
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

// hash function
unsigned int hash_Table::hash(char * word)
{
	unsigned int hashVal = 0;
	for (char ch : word)
	{
	hashVal = 37 * hashVal + ch;
	}
	
	return hashVal;
}

// get next prime number for rehashing the table
int hash_Table::getNextPrime()
{
	unsigned int N = tableSize * 2;
	return something...
}


