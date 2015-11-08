#include "Word.h"
#include <vector>
#include <iostream>

using namespace std;

class hash_Table
{
	public:
		hash_Table(int size);

		void insert(char * word);
		void remove(char * word);

		// getters
		float get_Lambda() const;
		unsigned int get_tableSize() const;
		unsigned int get_numElements() const;

	private:
		word item; 				// word being placed into hash table
		vector<word> table;		// hash table

		void rehash();
		unsigned int hash(char * string);	//returns a position, so it's an unsigned int
		unsigned int find_Pos(char * string);
		void makeEmpty();

		int get_nextPrime(int num);
		bool isPrime(int num);

		float lambda;			// load factor
		unsigned int tableSize;			// the size of the hash_Table
		unsigned int numElements;		// how may words are currently in the hash_Table
		
};

