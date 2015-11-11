#include "Word.h"

// constructor
word::word(const char * string)
{
	info = 0;	// 0 = empty
	set_Length(string); 
	set_Item(string);
}

word::word()
{
	info = 0; // 0 = empty
}

//default destructor?
word::~word() {}

// getter for item
const char * word:: get_Item() const
{
	return item;
}

// getter for length - may not need this. Could be useful in the print function later on
int word:: get_Length() const
{
	return length;
}

// override == operator
bool word::operator == (const word & rhs) const
{
	return get_Item() == rhs.get_Item();
}

//override != operator
bool word::operator != (const word & rhs) const
{
	return !(*this == rhs);
}

// setter for length. I don't know if we really need this or not.
void word::set_Length(const char * string)
{
	length = strlen(string); //check this?
}

//setter for item
void word::set_Item(const char * string)
{
	item = string;
}


