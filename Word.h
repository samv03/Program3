#include <cstring>

class word
{
	public:
		word();
		~word();

		int frequency;

		enum EntryType {ACTIVE, EMPTY, DELETED};

		EntryType info;

		void set_Item(char * string);
		const char * get_Item() const;
		char * get_Length() const;
		bool operator == (const word & rhs) const;
		bool operator != (const word & rhs) const;
	
	private:
		char * item;
		int length;

		void set_Length(char * string);

};
