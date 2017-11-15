/*****************ll1.cpp**************/	//(LL1.cpp)
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/11/15
//Compiled with gcc
//Written on vim & visual studio
//Purpose: Parse a language using 
// and LL(1) parsing table
/***************************************/

#include <iostream> //input/output library
#include <cstdlib> //general purpose C library
#include <vector> //vector data structure
#include <fstream> //file stream
using namespace std;

//input file rules to create grammar table
ifstream rules;

//grammar stack (vector in order to display)
vector <char> theStack;

//valid chars are S A B 0 1

//grammar rule table
string theTable[4][6] = {
{" ", "S", "A", "B", "0", "1"},
{"S", " ", " ", " ", " ", " "},
{"A", " ", " ", " ", " ", " "},
{"B", " ", " ", " ", " ", " "}
};

/*       Test Table
$   S   A   B   0   1

S   -   -   -  0A0 1A1 

A   -   -   -  0 0 1 1

B   -   -   -   -   -

  0 1 2 3 4 5
0 $ S A B 0 1
1 S
2 A
3 B
*/



/*************************Start of functions****************************/

//Purpose: take rules specified in rule file and
// put them into the grammar table for future access
//Parameters: none
//Algorithm: uses first char on line to determine row
// uses second char to determine column
// takes second char and remaining char and appends them together
// take resulting string and puts them at location dependant
// on row and col.
//Input: none
//Output: none
void setRules()
{
	rules.open("rules");

	int count = 0;	//first or second char in rule
	int row = 0;	//table row location
	int col = 0;	//table column location
	char hold;	//hold rule char
	string theString;	//hold is appended to this to create whole rule

	while(rules >> hold)	//while rules can read in
	{
		switch(hold)
		{
			case 'S':	//non terminal found
				if(count == 0)	//if it is the lhs
					row = 1;
				else if(count == 1)	//rhs
				{
					col = 1;
					theString += hold;
				}
				else
					theString += hold;
				count++;
				break;
			case 'A':
				if(count == 0)
					row = 2;
				else if(count == 1)
				{
					col = 2;
					theString += hold;
				}
				else
					theString += hold;
				count++;
				break;
			case 'B':
				if(count == 0)
					row = 3;
				else if(count == 1)
				{
					col = 3;
					theString += hold;
				} 
				else
					theString += hold;
				count++;
				break;
			case '0':	//terminal found, must be rhs
				if(count == 1)	//is it the first char on rhs?
				{
					col = 4;
					theString += hold;
				}
				else
					theString += hold;
				count++;
				break;
			case '1':
				if(count == 1)
				{
					col = 5;
					theString += hold;
				}
				else
					theString += hold;
				count++;
				break;
			case '$':	//end of rule
				theTable[row][col] = theString;	//take the rule and put it into the table
				//reset for next rule
				count = 0;
				row = 0;
				col = 0;
				theString = "";
				break;
			default:	//char was not valid
				printf("Invalid rule: %c", hold);
				return;
		}
	}
	rules.close();
}


//Purpose: output the list of grammar rules to the screen
//Parameters: none
//Algorithm: loops through table from top left to bottom right
//Input: none
//Output: outputs to screen
void readRules()
{
	for(int row = 1; row < 4; row++)
	{
		for(int col = 1; col < 6; col++)
		{
			printf("row %s col %s : %s\n", theTable[row][0].c_str(), theTable[0][col].c_str(), theTable[row][col].c_str());
		}
	}
}


//Purpose: output the contents of the stack to the screen
//Parameters: none
//Algorithm: loops from top of vector to the bottom
//Input: none
//Output: outputs to screen
void displayStack()
{
	printf("Stack\n");
	
	if(theStack.empty())
		printf("[ empty ]\n");
	else
	{	//reads from top of vector to the bottom to mimic stack
		for (int count = theStack.size()-1; count >= 0; count--)
			printf("%c\n", theStack.at(count));
	}
	printf("------------------\n");
}


//Purpose: check if two chars match
//Parameters: compare and matchThis
//Algorithm: == comparison
//Input: none
//Output: true for match, false for not
bool match(char compare, char matchThis)
{
	if (compare == matchThis)
		return true;
	else
		return false;
}


//Purpose: parse a string of 0's and 1's using
// a stack and a predefined set of grammar rules
// using leftmost derivation
//Parameters: parseThis, the user input that is to
// be parsed
//Algorithm: pulls first char off the stack, checks char
// for match with predefined non-terminals, if match, rhs
// should be applied, checks first char in user input with,
// predefined terminals, if matched twice, goes to location
// in the grammar table, takes string at location and pushes
// it onto the stack. if terminal is found on loop, no rhs
// is applied, checks for match with top of stack and first
// char in user input, if match pop off stack, pop off string.
// Loops
//
// -Errors
// if non-term finds an invalid term after, user input something
// other than 1's and 0's
// if terminal does not match, mismatch has occured, string does
// not exist in the language
// if default, stack contains an invalid character, rules have
// an undefined char in them
//Input: none
//Output: none
void LLParse(string parseThis)
{
	char pullStack;		//hold char on top of stack
	string theRule;		//hold the rule from grammar table
	bool rhs = false;	//rhs should or should not be applied
	int row = 0;		//row location for table
	int col = 0;		//column location for table
	bool result;		//result of match()

	while (!theStack.empty())
	{
		displayStack();
		printf("Current char is: %c\n", parseThis[0]);
		
		pullStack = theStack.back();	//pull top value from stack
		theStack.pop_back();
	
		switch (pullStack)	//parse top stack value
		{
		case 'S':		//non-terminal on stack
			row = 1;
			rhs = true;
			if(parseThis[0] == '0')	//check next terminal
				col = 4;
			else if(parseThis[0] == '1') //check next terminal
				col = 5;
			else	//next terminal is invalid
			{
				rhs = false;
				printf("Error. Input included something other than 0's and 1's: %c\n\n", parseThis[0]);
				return;
			}
			break;
		case 'A':		//non-terminal on stack
			row = 2;
			rhs = true;
			if(parseThis[0] == '0')
				col = 4;
			else if(parseThis[0] == '1')
				col = 5;
			else
			{
				rhs = false;
				printf("Error. Input included something other than 0's and 1's: %c\n\n", parseThis[0]);
				return;
			}
			break;
		case 'B':		//non-terminal on stack
			row = 3;
			rhs = true;
			if(parseThis[0] == '0')
				col = 4;
			else if(parseThis[0] == '1')
				col = 5;
			else
			{
				rhs = false;
				printf("Error. Input included something other than 0's and 1's: %c\n\n", parseThis[0]);
				return;
			}
			break;
		case '0':	//terminal on stack
			result = match('0', parseThis[0]);	//match it with user input char
			if (!result)
			{
				printf("mismatch error\n");
				return;
			}
			else	//matche succeeded, remove from stack and input
			{
				parseThis.erase(parseThis.begin());
				printf("matched!\n\n");
			}
			break;
		case '1':	//terminal on stack
			result = match('1', parseThis[0]);
			if (!result)
			{
				printf("mismatch error\n");
				return;
			}
			else
			{
				parseThis.erase(parseThis.begin());
				printf("matched!\n\n");
			}
			break;
		default:
			printf("Invalid character on the stack: %c", pullStack);
			return;
		}
		if(parseThis[0] == '\0' && !theStack.empty())	//check for end of string char
		{
			displayStack();
			printf("Failure - input too short\n");
			return;
		}
		if(rhs)		//check if rhs should be applied
		{
			theRule = theTable[row][col];
			printf("Adding rhs of a rule to the stack\n\n");
			while(!theRule.empty())	//push rhs rule onto stack
			{
				theStack.push_back(theRule[0]);
				theRule.erase(theRule.begin());
			}
			rhs = false;
		}
	}
	displayStack();
	printf("Success!!\n");	//stack and input is empty
}


//Purpose: Driver for LL parse functions and user input
//User information: compile and run, then input a string
// of 0's and 1's when prompted and hit enter
//Algorithm: function calls
//Input:  gets user input in the form of a string of 0's and 1's
//Output: none
int main()
{
	string userInput;	//hold user input

	setRules();		//initialize rule table from file
	readRules();		//output rule table

	printf("Enter a string made of either 0's and/or 1's: ");
	cin >> userInput;	//get user input string of 0/1

	//error checking in parser

	theStack.push_back('S');	//initialize start of stack

	LLParse(userInput);	//begin LL parse on user input

	return 0;
}
