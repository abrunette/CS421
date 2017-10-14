#include <iostream>
#include <string>
#include <cstdlib>
#include "queue.h"
using namespace std;
// include queue.h or equivalent 

// CS421 HW1 Write a generator in C++ for L = {x | x is a binary number}.
// Your name: Aaron Brunette

// Copy the recognizer function here from the other file.

//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is 0 or 1. (leading 0's are allowed).
bool recognizer(string s)
{
	for(int counter = 0; counter < s.size(); counter++)	//cycle through user string
	{
		if(s[counter] != '0' && s[counter] != '1')	//check that all digits are 0 or 1
			return false;	//fails if not 1 or 0
	}
	return true;	//all digits are valid
}

// main: It should create each string over E = {0,1,2} systematically
//   (short to long) and pass each string to the recognizer function
//   created in Part a).  Hint: use a queue to generate strings
//   Only those strings for which the recognizer returned TRUE
//   should be displayed. 
//   keeps on going until the queue overflows 
int main()
{ 
	queue stringQueue;  	//initialize queue names stringQueue
	int input;		//holds user input to run or stop program
	int numGenCount = 0;	//count the amount of numbers generated
	bool result = false;	//checks if value is a valid binary number

	stringQueue.add("0");	//adds char 0 before loop
	stringQueue.add("1");	//adds char 1 before loop
	stringQueue.add("2");	//adds char 2 before loop

	//Asks user to start program
	cout << "Input 1 to start the binary number generator: "; cin >> input; cout << endl;
	if(input != 1)	//checks input
	{
		cout << "Ending Program!" << endl; exit(1);	//ends program
	}

    	while(input == 1) 	//loop -- indefinitely
    	{	
      		try	//begins adding and removing to queue to print strings
		{
			string temp; //local temp variable to hold string from queue
			stringQueue.remove(temp);	//removes front and stores in temp

			result = recognizer(temp);
			if(result == true)
			{
				cout << temp << endl;		//couts front
				numGenCount++;			//increment generated number count
				if(numGenCount >= 25)	//check if at least 25 numbers have been generated
				{
					cout << "At least 25 binary numbers have been generated.\nEnter 1 to continue: ";
						cin >> input;	//user input
					if(cin.fail())	//input check
						input = 0;
				}
			}
			stringQueue.add(temp + '0');	//re-adds front with 0
			stringQueue.add(temp + '1');	//re-adds front with 1
			stringQueue.add(temp + '2');	//re-adds front with 2
		}

      		catch(queue::Overflow) //error for full queue
		{	cerr << "Error: Overflow, too many items in queue." << endl; exit(1);	}
		catch(queue::Underflow) //error for empty queue
		{	cerr << "Error: Underflow, no items in queue." << endl;	exit(1); }
		catch (char const* errorcode) //error for invalid item
			{ cerr << "Error: " << errorcode << endl; exit(1); }
	}
}
