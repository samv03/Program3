#include "Word.h"

// constructor
word::word(char * string)
{
	item = string;
	info = EMPTY;
	set_Length(string); 
	set_Item(string);
}

//default destructor?
word::~word();

// getter for item
const char * word:: get_Item() const
{
	return item;
}

// getter for length - may not need this. Could be useful in the print function later on
const char * word:: get_Length() const
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
void word::set_Length(char * string)
{
	length = strlen(string);
}

//setter for item
void word::set_Item(char * string)
{
	item = string;
}


