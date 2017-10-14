#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// CS421 File fa.cpp for HW3
// Your name: Aaron Brunette

// ** Change this to fit the HW3C specification - look for **
// ** Must have the same types of tracing couts as mytoken.

// MYTOKEN DFA done by Rika Sensei has a sample
 // This FA is for a b^+
bool mytoken(string s)
{ 
  int state = 0;
  int charpos = 0;

  cout << "Trying the mytoken machine..." << endl;  
 
  while (s[charpos] != '\0') 
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
 
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	{
	  cout << "I am stuck in state " << state << endl;
	  return(false);
	}
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
}


// IDENT DFA 
 // This FA is for **
bool ident_token(string s)
{
  // ** complete this based on mytoken

  int state = 0;
  int charpos = 0;

  cout << "Trying the ident_token machine..." << endl;  


  while(s[charpos] != '\0')
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
 
	if (state == 0 && s[charpos] == 'a')
      	state = 1;
      	else
	if(state == 0 && s[charpos] == 'b')
	state = 1;
	else
      	if (state == 1 && s[charpos] == 'a')
      	state = 1;
      	else
      	if (state == 1 && s[charpos] == 'b')
      	state = 1;
	else
      	if (state == 1 && s[charpos] == '2')
      	state = 1;
	else
      	if (state == 1 && s[charpos] == '3')
      	state = 1;
	else
      	if (state == 1 && s[charpos] == '_')
      	state = 1;
      	else
	 {
	  cout << "I am stuck in state " << state << endl;
	  return(false);
	 }
         charpos++;
    }//end of while

  // where did I end up????
  if (state == 1) return(true);  // end in a final state
   else return(false);
}


// REAL DFA 
// This FA is for **
bool real_token(string s)
{
  // ** complete this based on mytoken

  int state = 0;
  int charpos = 0;

  cout << "Trying the real_token machine..." << endl;  


  while(s[charpos] != '\0')
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
 
	if (state == 0 && s[charpos] == '2')
      	state = 0;
      	else
	if(state == 0 && s[charpos] == '3')
	state = 0;
	else
      	if (state == 0 && s[charpos] == '.')
      	state = 1;
	else
      	if (state == 1 && s[charpos] == '2')
      	state = 2;
	else
      	if (state == 1 && s[charpos] == '3')
      	state = 2;
	else
      	if (state == 2 && s[charpos] == '2')
      	state = 2;
	else
      	if (state == 2 && s[charpos] == '3')
      	state = 2;
      	else
	 {
	  cout << "I am stuck in state " << state << endl;
	  return(false);
	 }
         charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
}


//INT DFA 
// This FA is for **
bool integer_token(string s)
{
  // ** complete this based on mytoken

  int state = 0;
  int charpos = 0;

  cout << "Trying the integer_token machine..." << endl;  


  while(s[charpos] != '\0')
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
 
	if (state == 0 && s[charpos] == '2')
      	state = 1;
      	else
	if(state == 0 && s[charpos] == '3')
	state = 1;
	else
      	if (state == 1 && s[charpos] == '2')
      	state = 1;
	else
      	if (state == 1 && s[charpos] == '3')
      	state = 1;
      	else
	 {
	  cout << "I am stuck in state " << state << endl;
	  return(false);
	 }
         charpos++;
    }//end of while

  // where did I end up????
  if (state == 1) return(true);  // end in a final state
   else return(false);
}

enum tokentype {ERROR, MYTOKEN, IDENT, REAL, INT};
int scanner(tokentype& , string& );  // to be called byy main
ifstream fin ("fain.txt", ios::in);  // input file stream


// The test-driver: to be completed **
int main()
{

  string tokens[5] = {"ERROR", "MYTOKEN", "IDENT", "REAL", "INT"};
  tokentype thetype;
  string theword; 

  while (true)  // keep on going 
    {
       if (theword == "EOF") break;
       scanner(thetype, theword);  // the paramers will be set by Scanner
       
       cout << "Type is:" << tokens[thetype]  << endl;
    }

  fin.close();
}

int scanner(tokentype& the_type, string& w)
{
  
  // This goes through all machines one by one on the input string

  cout << "\n.....Scanner was called..." << endl;

  fin >> w;  // grab next word from fain.txt
  cout << "Word is:" << w << endl;   
/*
  if (mytoken(w))
    { the_type = MYTOKEN; }
  */  
  // ** add other if-then's here in the right order to go through
  // all FAs one by one and set the_type to be IDENT, REAL or INT.

	if(ident_token(w))
	{ the_type = IDENT; }

	else if(real_token(w))
	{ the_type = REAL; }

	else if(integer_token(w))
	{ the_type = INT; }

  else //none of the FAs returned TRUE
   { cout << "Lexical Error: The string is not in my language" << endl;
      the_type = ERROR; }

}//the very end of scanner




