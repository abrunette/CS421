#include<iostream>
#include<string>
using namespace std;

// CS421 HW1 Write a recognizer in C++ for L = {x | x is a binary number}.
// Your name: Aaron Brunette

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
	return true;
}

//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout YES IN L or NO NOT IN L depending on what was returned.
int main()
{
	string userNumber;	//string to hold user input

	cout << "Welcome to the binary number recognizer.\n\nPlease input a number and I will tell you if it is a valid binary number:\n";

	if(!getline(cin, userNumber)) {return -1;}	//make sure cin works, else I/O error

	if(userNumber.empty()) {cout << "\nNothing was entered. Ending program."; return 0;}	//checks that something was entered, else ends program

	bool result = recognizer(userNumber);	//calls recognizer function

	if(result == true)	//checks that results from recognizer function are valid
		cout << "YES IN L\n";
	else	//fails
		cout << "NO NOT IN L\n";

	return 0;	//end program
}
