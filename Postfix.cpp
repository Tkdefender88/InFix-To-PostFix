/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Postfix Class Implementation
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef POSTFIX_IMP
#define POSTFIX_IMP

#include "Postfix.h"
#include "LinkedStack.h"

// Constructors implemented

Postfix::Postfix(std::string infix) : infix(infix)
{
	// should do something with the infix parameter value
}

std::string Postfix::formPostfix(std::string)
{
	LinkedStack<std::string> stack = LinkedStack<std::string>();

	for (char &c : infix)
	{
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			std::string topStack = stack.peek();
			break;
		}
	}
}

// Privare methods implemented

// Public methods implemented

std::string Postfix::getInfix()
{
	return infix;
}

std::string Postfix::getPostfix()
{

	return "";
}

double Postfix::getResult()
{
	return 0.00;
}

#endif