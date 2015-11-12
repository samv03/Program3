#include "Hash_Table.h"
#include <math.h>

// constructor
hash_Table::hash_Table(int size)
{
	table.resize(size);
	tableSize = size;
	makeEmpty();
}


//gonna need a destructor for points, even though we don't allocate anything
//hash_Table::~hash_Table() {}

// insert - modified from book
void hash_Table::insert(word * string)
{
	//cout << "Inserting into Hash" << endl;
	// send to hash function
	unsigned int pos = hash(string->get_Item());

	// see if it is already in the table
	unsigned int found = find_Pos(string->get_Item());
	if (table[found].info == 1)		// if active, increment frequency
	{
		cout << "Item: " <<  string->get_Item() << endl;
		table[found].frequency++;
		cout << "Freq: " << table[found].frequency << endl;
	}

	else
	{
		//cout << "Inside else" << endl;
		table[pos].set_Item(string->get_Item());
		table[pos].frequency = 1;
		table[pos].info = 1;		// set the entryType to active if empty
		numElements++;
		setLambda();
	}

	//check lambda value
	//float loadFactor = get_Lambda();
	
	// if too high, rehash the table, else return from function
	if (get_Lambda() >= 0.75)
	{
		rehash();
		return;
	}

	else
		return;
}

// find - modified from book
// Needs work
unsigned int hash_Table::find_Pos(const char * string)
{
	//get hash value and start traversal there
	unsigned int pos = hash(string);
	
	// traverse vector "table" and see if the current entry is 
		// not deleted and has the same char * string as the one we're trying to find
	//this loop will drop out once it reaches an empty position (will not go forever!)
	while (table[pos].info != 0 && table[pos].get_Item() != string)
	{
		cout << "Pos: " << pos << endl;
		//cout << "in find_pos" << endl;
		pos ++;				//using linear probing
		if (pos >= tableSize)
		{
			pos -= tableSize;
		}
	}

	return pos;
}

// delete - modified from book
	// get hash value
	// traverse vector "Table" until you find the item
	// mark the item .info as EMPTY
void hash_Table::remove (word * string)
{	
	int pos = hash(string->get_Item());
	if (table[pos].info == 1)		// 1 = active
		table[pos].info = 2;		// 2 = deleted

}

// hash function (direct from book, with speed modifications learned in CSC314)
unsigned int hash_Table::hash(const char * word)
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
		table[i].info = 0;				// 0 = empty

	numElements = 0;

	for (unsigned int i = 0; i < tableSize; i++)
	{
		if (table[i].info == 1)				// if active, move to new vector and increment number of elements
		{
			word * moveWord = new (nothrow) word (table[i].get_Item());
			insert(moveWord);
			//insert( std:: move (table[i].get_Item()) ) ;
			numElements++;
		}
	}

	cout << "Rehash complete." << endl;
}

// get next prime number after the one you input for rehashing the table
// Needs work with for-loop
int hash_Table::get_nextPrime(int num)
{
	bool prime;	

	//add one to the number passed in until you find a prime number
	for (int i = num * 2 ; i < num * num; i++)
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

	for (int i = 1; i < sqrt(num) + 1; i++)
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
		entry.info = 0; 	// set each element as empty
}

//get lambda
float hash_Table::get_Lambda() const
{
	return lambda;
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

void hash_Table::setLambda()
{
	lambda = float(numElements)/float(tableSize);
}

