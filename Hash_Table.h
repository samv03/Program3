#include "Word.h"
#include <vector>
#include <iostream>

using namespace std;

class hash_Table
{
	public:
		hash_Table(int size);

		void insert(const char * word);		// inserts word into hash table
		void remove(const char * word);		// removes word from hash table

		// getters
		float get_Lambda() const;		// returns lambda/load factor
		unsigned int get_tableSize() const;	// returns the size of the hash table
		unsigned int get_numElements() const;	// returns the number of elements in the hash table

	private:
		word item; 				// word being placed into hash table
		vector<word> table;		// hash table

		void rehash();
		unsigned int hash(const char * string);	// returns a position, so it's an unsigned int
		unsigned int find_Pos(const char * string);	// our find function, returns a position
		void makeEmpty();			// forces each element in the hash table to be empty

		int get_nextPrime(int num);		// finds the new table size for rehashing 
		bool isPrime(int num);			// checks to see if a number is prime

		float lambda;				// load factor
		unsigned int tableSize;			// the size of the hash_Table
		unsigned int numElements;		// how may words are currently in the hash_Table
		
};

