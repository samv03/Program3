#include <cstring>

class word
{
	public:
		word(const char * string);
		word();
		~word();

		int frequency;

		//enum EntryType {ACTIVE, EMPTY, DELETED};
		//EntryType info;

		// 0 = empty
		// 1 = active
		// 2 = deleted
		int info;

		void set_Item(const char * string); //
		const char * get_Item() const;
		int get_Length() const;
		bool operator == (const word & rhs) const;
		bool operator != (const word & rhs) const;
	
	private:
		const char * item;
		int length;

		void set_Length(const char * string);

};
