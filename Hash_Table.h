#include "Word.h"

class hash_Table
{
	public:
		hash_Table;
		~hash_Table;

		enum EntryType {ACTIVE, EMPTY, DELETED};

		void insert(char * word);
		void remove(char * word);
		bool find (char * word);
	
		// getters
		float get_Lambda();
		int get_tableSize();
		int get_numElements();

	private:
		word item; 				// word being placed into hash table
		vector<word> table;		// hash table

		void rehash();
		unsigned int hash(char * string);
		int findPos( const char * string);

		int get_NextPrime();

		float lambda;			// load factor
		int tableSize;			// the size of the hash_Table
		int numElements;		// how may words are currently in the hash_Table

		
};

