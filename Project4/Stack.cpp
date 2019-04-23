// Author:	   Grant Sowards
// Assignment:	   project 3
// File:	   project3.cpp, stack.cpp, queue.cpp
// Instructor:	   Reza Sonati
// Class:	   CS 2420  Section: 001 
// Date Written:   5/24/2015 
// Description:  Stack and Queue

// I declare that the source code contained in this assignment was written solely by me.
// I understand that copying any source code, in whole or in part,
// constitutes cheating, and that I will receive a zero on this project
// if I am found in violation of this policy.

#include "Stack.h"
#include "stdafx.h"
//Constructor definition for Stack 
Stack::Stack()
{
	top = NULL;
}

// Function Name:	string Stack::push(node_entry item)
// Purpose:	  add item to top of stack
// Parameters:	node_entry
// Returns:	   string
// Pre-conditions:	
// Post-conditions: 
string Stack::push(Node* item)
{
	Stack_Node *p = new Stack_Node(item);
	if (top == NULL)
	{
		top = p;
	}
	else
	{
		p->nlink = top;
		top = p;
	}
	stack_count++;
	return "success";
}

// Function Name:	string Stack::pop()
// Purpose:	  remove item to top of stack
// Parameters:	
// Returns:	   string
// Pre-conditions:	
// Post-conditions: 
string Stack::pop()
{
	if (top == NULL)
	{
		return "underflow";
	}
	else
	{
		Stack_Node *p;
		p = top;
		top = top->nlink;
		delete p;
		stack_count--;
		return "success";
	}
}

// Function Name:	void Stack::traversePrint(void(*visit)(Stack_Node *p))
// Purpose:	  traverse stack and print each item
// Parameters:	Print function
// Returns:	   void
// Pre-conditions:	
// Post-conditions: 
void Stack::traversePrint(void(*visit)(Stack_Node *p))
{
	Stack_Node *p;
	p = top;
	if (top == NULL)
	{
		cout << "\nNo items in Stack!";
	}
	else
	{
		while (p != NULL)
		{

			(*visit)(p);
			p = p->nlink;
		}
	}

}

// Function Name:	void Stack::clear()
// Purpose:	  clear items in stack
// Parameters:	
// Returns:	   void
// Pre-conditions:	
// Post-conditions: 
void Stack::clear()
{

	while (top != NULL)
	{
		Stack_Node *p;
		p = top;
		//cout << "\nDeleted "<<p->entry;
		top = top->nlink;
		delete p;
		delete_count++;
	}
}

//node constructor
Stack_Node::Stack_Node(node_entry item)
{
	entry = item;
}