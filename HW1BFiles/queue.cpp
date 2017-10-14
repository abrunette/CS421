//INSTRUCTION
//Look for **
//Fill in the function body
//When done, compile queue.cpp to make sure it has no syntax errors

//=========================================================
//HW#: HW1P1 queue
//Your name: Aaron Brunette
//Complier:  g++
//File type: client
//===========================================================

using namespace std;
#include <iostream>
#include "queue.h"  
#include <cstdlib>

// constructor 
queue::queue()
{ front = 0; rear = -1; count = 0; }	//initializes queue values

//destructor 
queue::~queue()
{	}	//nothing to do

// PURPOSE: returns true if queue is empty, otherwise false
bool queue::isEmpty()
{	if (count == 0) return true; else return false; }	//checks if queue is empty

// PURPOSE: returns true if queue is full, otherwise false
bool queue::isFull()
{	if (count == MAX_SIZE) return true; else return false;}	//checks if queue is full

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear 
// PAREMETER: provide the element (newElem) to be added
void queue::add(el_t newElem)
{	if (isFull()) throw "Overflow, Queue is full.";	//overflow error

	else
	//adds element to rear and replaces rear then increments queue size
	{ rear = (rear+1) % MAX_SIZE; el[rear] = newElem; count++;}	
}

// PURPOSE: if empty, throw Underflow
// if not empty, removes the front element to give it back 
// PARAMETER: provide a holder (removedElem) for the element removed (pass by ref)
void queue::remove(el_t& removedElem)
{	if (isEmpty()) { throw "Underflow, Queue is empty."; } 	//underflow error
	
	else
	//removes front element then decrements queue size
	{ removedElem = el[front]; front = (front+1) % MAX_SIZE; count--; }
}

// PURPOSE: if empty, throws an exception Underflow
// if not empty, give back the front element (but does not remove it)
//PARAMETER: provide a holder (theElem) for the element (pass by ref)
void queue::frontElem(el_t& theElem)
{	if (isEmpty()) { throw "Underflow, Queue is empty. No front element."; }	//underflow error

	else
	{ theElem = el[front]; }	//returns front element
}

// PURPOSE: returns the current size to make it 
// accessible to the client caller
//PARAMETER: None
int queue::getSize()
{	return count; }		//returns queue size

// PURPOSE: display everything in the queue horizontally from front to rear
// enclosed in []
// if empty, displays [ empty ]
//PARAMETER: None
void queue::displayAll()
{	if (getSize() == 0) { cout << "[ empty ]" << endl; }	//tests queue size

	cout << "Displaying queue." << endl;
	int Fhold = front;	//front location
	int Rhold = rear;	//rear location
	while (Fhold != Rhold)	//checks for overlap
	{
		if(Fhold++ == MAX_SIZE-1)	//wraps queue around
			Fhold = 0;		//sets location to beginning of queue

		else
		{
			el_t Stemp;	//temp variable for string
			remove(Stemp);	//remove and hold front
			cout << Stemp << endl;	//displays front
			Fhold++;	//increments front to next item
		}
	}
}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear by
//doing remove followed by add.
//PARAMETER: None
void queue::goToBack()
{	//no local variable
	if (isEmpty()) //checks if queue is empty
	{
		//throws underflow error if queue is empty
		throw "Underflow, Queue is empty. Nothing to go back to.";
	}

	//checks if queue size is equal to 1, then exits if true
	else if (getSize() == 1) { exit(1); }
	
	//checks if queue size is greater than 1, then goes to back if true
	else if (getSize() > 1) { remove(el[front]); add(el[rear]); }
}





