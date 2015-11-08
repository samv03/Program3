#include "Word.h"

// constructor
word::word(char * string)
{
	item = string;
	info = EMPTY;
	set_Length(string); 
}

//default destructor?
word::~word();

// getter for item
const char * word:: get_Item() const
{
	return item;
}

// getter for length
const char * word:: get_Length() const
{
	return length;
}

// override == operator
bool word::operator == (const word & rhs) const
{
	return (
}

//override != operator
bool word::operator != (const word & rhs) const
{

}


// setter for length
void word::set_Length(char * string)
{
	length = strlen(string);
}


//setter for item
void word::set_Item(char * string)
{
	item = string;
}


