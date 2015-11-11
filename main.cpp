/*************************************************************************//**
 * @file 
 *
 * @brief This file contains the main function and additional functions
 * which take advantage of the Linklist class.
 *
 * @mainpage Program 3 - Reverse Typoglycemia
 * 
 * @section course_section Course Information 
 *
 * @author Samuel Vinella
 * 
 * @date April 14, 2014
 * 
 * @par Professor: 
 *         Roger Schrader
 * 
 * @par Course: 
 *         CSC 250 - M001 - 11:00am
 * 
 * @par Location: 
 *         Classroom Building - Room 204W
 *
 * @section program_section Program Information 
 * 
 * @details ]
 * This program's functionality is to take files given from the command
 * line by the user, and reverse the typoglycemia and then output it
 * to the file. 
 *
 * To accomplish this it first takes a dictionary that is with the
 * program files and inputs it into a singly linked list. It then
 * inputs words from the input file given by the user one at a time.
 * It then removes punctuations and capitalization from the word. Next
 * it tests if the word is long enough to have the interior letters
 * jumbled. If the word is long enough, it permutes the word looking
 * for all possible combinations. On each combination it tests to see
 * if the word is in the dictionary, if it is it stops the 
 * permutation and returns the word. It then puts the capitalization
 * and punctuation back on the word if it was found in the dictionary.
 * If it wasn't in the dictionary it puts a star in front of the word.
 * It then looks at the next character in the stream to see if it is 
 * a newline, if there is a newline it will output one after the word.
 * If there is not a newline then it will only add a space after the
 * word. It then outputs the word to a file preserving the spacing
 * found earlier.
 * 
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      Visual Studio 2012 used to compile
 * 
 * @par Usage: 
   @verbatim  
   Usage: c:\\>  prog3.exe  message.txt  result.txt

   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug No known bugs.
 * @todo None
 * 
 *
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Apr 1, 2014   Started program. Constructed command line code and set up
				 opening each of the 3 files.
   Apr 2, 2014   Made the dictionary insertion into the linklist. Set up the
				 input from the input file. Constructed the format and
				 permutation functions
   Apr 5, 2014   Made the loadcharacters function and reformat word function
   Apr 13, 2014  Tested the program for the first time and fixed many many
				 bugs. Made the clearArray, openOutFile, and print functions.
   Apr 14, 2014  Added inline comments and doxygen
			     Submitted program.
   @endverbatim
 *
 *****************************************************************************/
//#include "Linklist.h"
#include <iostream>
#include <ostream>
#include <fstream>
//#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const char* DELIMITERS = " ,.*!<>:()?;-";
const char* VALID = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/

void openFile( ifstream &fin, char *argv);
void formatWord(string &word, bool &empty);
void clearArray(int *used, int index);
void tokenize1( const string& str, vector<string>& tokens, const string& delimiters);
void tokenize2( const string& str, vector<string>& tokens, const string& valid);
void print(string word, ostream &out, bool newlinechk);

/**************************************************************************//**
 * @author Samuel Vinella
 *
 * @par Description:
 * This is the main manager of the program and will call other functions
 * to accomplish the goal of reversing the typoglycemia of the input file
 * and outputting it to the output file.
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - an array of characters containing the arguments.
 *
 * @returns 0 success
 * @returns 1 failed
 *
 *****************************************************************************/

int main(int argc, char **argv)
{
	//initializing variables
	string word, result;
	ifstream fin;
	ofstream fout;
	//LinkList list;
	bool empty = false, newlinechk = false;
	char chars[100], peek;
	int n = 0, pos = 1, used[100] = {0}, i = 0;

	//check for incorrect number of arguements, output error if true
	if(argc != 2)
	{
		cout << "ERROR: Incorrect number of arguements" << endl <<
			"Usage: c:\\>  program3.exe  input.txt " << endl;
		return 1;
	}

	openFile(fin, argv[1]);
	

	//get each word from the input file
	while( fin >> word)
	{
		//calls the function to format the word, removing upper case and punct
		formatWord(word, empty);

		//look at the next character in the stream
		peek = fin.peek();
		//if it is a newline set newlinechk to true
		if(peek == '\n')
			newlinechk =true;
        
        if( !empty)
        {
            print(word, cout, newlinechk);
            cout << endl;
        }
		//clear used array and set checks to false
		clearArray(used, 100);
		empty = false;
		newlinechk = false;
	}
	//close the file and return 0
	fin.close();
	return 0;
}	

/**************************************************************************//** 
 * @author Sam Vinella
 * 
 * @par Description: This function will open the output file and if it
 * fails it will output an error message and exit the program.
 * 
 * @param[in, out] fin - input file stream
 * @param[in] argv - input file name
 *  
 *****************************************************************************/

void openFile( ifstream &fin, char *argv)
{
	fin.open(argv);
	if(!fin)
	{
		cout << "ERROR: Input file failed to open" << endl;
		exit(0);
	}
	return;
}

/**************************************************************************//** 
 * @author Sam Vinella
 * 
 * @par Description: This function will take off punctuation and make the word
 * lowercase. It will pass back the punctuation and if the word was
 * capitalized.
 * 
 * @param[in, out] word - word to be formatted
 * @param[in, out] capital - capital check to be given back to main for the
							 reformatting
 * @param[in, out] punc - punctuation to be given back to main for the 
						  reformatting
 *  
 *****************************************************************************/

void formatWord(string &word, bool &empty )
{
	//initialize iterator
	string::iterator it;
    bool intApos = true, number = false, begApos = false;
    vector<string> tokens;
    
    it = word.begin();
    /*
    while( (*it < 65 || *it > 122 || (*it > 90 && *it < 97)) && it != word.end() - 1)
    {
        word.erase(it);
        it = word.begin();
    }
    
    
    
    it = word.begin();
    
    
	if(isupper(*it))
	{
		capital = true;
		*it = tolower(*it);
	}

	//set the iterator to the end, then move back one spot
	it = word.end();
	it--;
    
    while( (*it < 97 || *it >122) && it != word.begin())
    {
        word.erase(it);
        it = word.end();
        it--;
    }
    */
    /*
    char * ptr;
    
    if(sizeof(word) == 0)
    {
        empty = true;
    }
    
    cout << "Before: " << word << endl;
    
    ptr = strtok(&word[0], ",!:.%#();[]<>");
    
    if( ptr != nullptr)
    {
        string word(ptr);
    }
    
    it = word.begin();
    for( ; it != word.end(); it++)
    {
        if(isupper(*it))
        {
            *it = tolower(*it);
        }
    }
    it = word.begin();
    if( *it == 39)
    {
        word.erase(it);
    }
    it = word.end();
    if( *it == 39)
    {
        word.erase(it);
    }
    */
    
	//cout << "Word: " << word << endl;
    for( ; it != word.end(); it++)
    {
		if( it == word.begin() && *it == 39 )
		{
			cout << "<<-----First!----->>" << endl;
			intApos = false;
			begApos = true;
		}
		else if( it == word.end() - 1 && (*it == 39 || *it == -103))
		{
			intApos = false;
			begApos = true;
		}
        if( int(*it) == -103 && !begApos)
        {
            if(it != word.end() - 1 && it != word.begin())
            {
				cout << "<<----HERE---->>" << endl;
                intApos = true;
            }
			else
			{
				intApos = false;
			}
        }
		if( *it > 47 && *it < 58 )
		{
			number = true;
		}
		else if( *it > 64 && *it < 91 )
		{
			*it = tolower(*it);
		}
    }
    
    if( intApos && (number || word.size() != 1) )
    {
		//cout << "T1 Word: " << word << endl;
        tokenize1( word, tokens, DELIMITERS);
    }
    else
    {
		//cout << "T2 Word: " << word << endl;
        tokenize2(word, tokens, VALID);
    }
    
	//cout << "After: " << tokens[0] << endl;
	if( !tokens.empty() )
	{
    	word = tokens[0];\
	}
	else
	{
		empty = true;
	}
    
	return;
}


/**************************************************************************//** 
 * @author Sam Vinella
 * 
 * @par Description: This function will set each spot in used to 0.
 * 
 * @param[in, out] used - pointer array to be set to 0
 * @param[in] index - number of spots to clear in the array
 *  
 *****************************************************************************/

void clearArray(int *used, int index)
{
	//initialize for variable
	int i;

	//step through the array setting everything to 0
	for( i = 0; i < index; i++)
	{
		used[i] = 0;
	}
}

void tokenize1( const string& str, vector<string>& tokens, const string& delimiters = " " )
{
    // skip delimiters to start of first token
    int tokenStart = str.find_first_not_of( delimiters, 0 );
    // find next delimiter (i.e., end of first token)
    int tokenEnd = str.find_first_of( delimiters, tokenStart );
    
    // loop through input string
    while ( tokenStart != string::npos )
    {
        // found a token, add it to the vector
        tokens.push_back( str.substr( tokenStart, tokenEnd - tokenStart ) );
        // skip delimiters to start of next token
        tokenStart = str.find_first_not_of( delimiters, tokenEnd );
        // find next delimiter (end of token)
        tokenEnd = str.find_first_of( delimiters, tokenStart );
    }
}

void tokenize2( const string& str, vector<string>& tokens, const string& valid = " " )
{
    // skip delimiters to start of first token
    int tokenStart = str.find_first_of( valid, 0 );
    // find next delimiter (i.e., end of first token)
    int tokenEnd = str.find_first_not_of( valid, tokenStart );
    // loop through input string
    while ( tokenStart != string::npos )
    {
        // found a token, add it to the vector
        tokens.push_back( str.substr( tokenStart, tokenEnd - tokenStart ) );
        // skip delimiters to start of next token
        tokenStart = str.find_first_of( valid, tokenEnd );
        // find next delimiter (end of token)
        tokenEnd = str.find_first_not_of( valid, tokenStart );
    }
}

/**************************************************************************//** 
 * @author Sam Vinella
 * 
 * @par Description: This function will print the word to either a file or
 * to the screen. It will also check newlinechk to see if there needs to 
 * be a space or newline after the word.
 * 
 * @param[in] word - word to be outputted
 * @param[in, out] out - ostream to output the word
 * @param[in] newlinechk - bool to check if there needs to be a space or a
 *						   newline.
 *  
 *****************************************************************************/

void print(string word, ostream &out, bool newlinechk)
{
	//output the word
	out << word;

	//if the word had a newline after, output it
	//if(newlinechk)
	//	out << endl;
	//if not, output a space
	//else
	//	out << " ";
}
