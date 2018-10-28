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

#include <map>
#include <stdexcept>

#include "Postfix.h"
#include "LinkedStack.h"

// Constructors implemented
Postfix::Postfix(std::string infix) : infix(infix)
{
	// should do something with the infix parameter value
	postfix = formPostfix(infix);
}

// Private methods implemented

// isOperator takes in a character parameter 'c' and returns true if
// 'c' is with an operator, otherwise false. Operators are defined
// as the following characters +, -, *, /, ^, (, )
bool Postfix::isOperator(const char c) const
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return true;
	default:
		return false;
	}
}

//isOperand takes in a character parameter 'c' and returns true if 'c'
//is with in the range of the normal alphabet capital or lowercase,
//otherwise false.
bool Postfix::isOperand(const char c) const
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

//higherPrecendence takes in two characters a and b, if they are operators
//returns true if 'a' has a higher precedence over 'b' or if 'a' is an operator and 'b'
//is the empty char otherwise false.
//Also returns false if the two characters are not operators.
bool Postfix::higherPrecedence(const char a, const char b)
{
	std::map<char, int> pRule = {
		{'(', 1},
		{')', 1},
		{'+', 2},
		{'-', 2},
		{'*', 3},
		{'/', 3},
		{'^', 4},
	};
	if (isOperator(a) && isOperator(b))
	{
		return pRule[a] > pRule[b];
	}

	//a always has precendence over an empty character
	if (isOperator(a) && b == '\0')
	{
		return true;
	}

	return false;
}

//balancedParen checks to see if a given string has balanced parentheses
//if all the parentheses match then it returns true otherwise false.
bool Postfix::balancedParen(const std::string infix) const
{
	LinkedStack<char> stack = LinkedStack<char>();
	bool success = true;
	for (char c : infix)
	{
		if (c == '(')
		{
			stack.push('(');
		}
		else if (c == ')')
		{
			if (!stack.pop())
			{
				success = false;
			}
		}
	}
	return success && stack.isEmpty();
}

// formPostfix takes in a parameter string in infix notation and
// converts it into postix and returns the resulting string
std::string Postfix::formPostfix(std::string infix) 
{
	LinkedStack<char> stack = LinkedStack<char>();
	std::string postfix = "";

	if (!balancedParen(infix))
	{
		throw std::invalid_argument("Parentheses in expression not balanced");
	}
	//goes through every character in the infix string
	for (char c : infix)
	{
		if (isOperator(c))
		{
			char topOp;
			if (stack.isEmpty())
			{
				topOp = '\0';
			}
			else
			{
				topOp = stack.peek();
			}

			if (higherPrecedence(c, topOp))
			{
				stack.push(c);
			}
			else
			{
				for (char op = topOp; !higherPrecedence(c, op) && op != '('; op = !stack.isEmpty() ? stack.peek() : '\0')
				{
					if (op != '(' && op != ')')
					{
						postfix += op;
					}
					stack.pop();
				}
				stack.push(c);
			}
		}
		else if (isOperand(c))
		{
			//add the operand to the postfix string
			postfix += c;
			std::size_t found = seen.find(c);
			if (found == std::string::npos)
			{
				seen += c;
			}
		}
		else if (c == '(' || c == ')')
		{
			if (c == '(')
			{
				stack.push(c);
			}
			else
			{
				for (char op = stack.peek(); op != '('; op = !stack.isEmpty() ? stack.peek() : '(')
				{
					postfix += op;
					op = stack.pop();
				}
			}
		}
		else
		{
			throw std::invalid_argument("encountered character that was not an operator or operand");
		}
	}

	//after the whole string has been evaluated pop all the characters
	//off the stack to the postfix string
	for (; !stack.isEmpty(); stack.pop())
	{
		if (stack.peek() != '(' && stack.peek() != ')')
		{
			postfix += stack.peek();
		}
	}
	return postfix;
}
// Public methods implemented

std::string Postfix::getInfix()
{
	return infix;
}

std::string Postfix::getPostfix()
{

	return postfix;
}

double Postfix::getResult()
{
	return 0.00;
}

#endif