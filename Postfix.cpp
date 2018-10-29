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
#include <iostream>
#include "math.h"

#include "Postfix.h"
#include "LinkedStack.h"

// Constructors implemented
Postfix::Postfix(std::string infix) : infix(infix)
{
	// should do something with the infix parameter value
	try
	{
		postfix = formPostfix(infix);
		getValues();
		result = calcResult();
	}
	catch (const PrecondViolatedExcep &e)
	{
		std::cout << e.what() << std::endl;
	}
}

// Private methods implemented

//getValues prompts the user for what each identifier holds
void Postfix::getValues()
{
	for (char c : seen)
	{
		double val;
		std::cout << "enter a value for: " << c << ": ";
		std::cin >> val;

		values[c] = val;
	}
}

//caclReuslt calulates the result of the infix expression and returns the result.
//throws PrecondViolatedExcep error
double Postfix::calcResult() const
{
	LinkedStack<double> *stack = new LinkedStack<double>();
	for (char c : postfix)
	{
		if (isOperand(c))
		{
			stack->push(values.find(c)->second);
		}
		else if (isOperator(c))
		{
			double operand2 = stack->peek();
			stack->pop();
			double operand1 = stack->peek();
			stack->pop();
			double result = 0;

			switch (c)
			{
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0)
				{
					throw(PrecondViolatedExcep("idiot error - you cannot divide by zero. It breaks the universe."));
				}
				result = operand1 / operand2;
				break;
			case '^':
				result = pow(operand1, operand2);
				break;
			}

			stack->push(result);
		}
	}
	double finalRes = stack->peek();
	stack->pop();
	delete stack;
	return finalRes;
}

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
	return (c >= 'a' && c <= 'z');
}

//higherPrecendence takes in two characters a and b, if they are operators
//returns true if 'a' has a higher precedence over 'b' or if 'a' is an operator and 'b'
//is the empty char otherwise false.
//Also returns false if the two characters are not operators.
bool Postfix::higherPrecedence(const char a, const char b)
{
	std::map<char, int> pRule = {
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
	LinkedStack<char> *stack = new LinkedStack<char>();
	bool success = true;
	for (char c : infix)
	{
		if (c == '(')
		{
			stack->push('(');
		}
		else if (c == ')')
		{
			if (!stack->pop())
			{
				success = false;
			}
		}
	}
	bool empty = stack->isEmpty();
	delete stack;
	return success && empty;
}

// removeSpaces takes in a string and removes all space ' ' characters
// from it and returns the resulting string
string Postfix::removeSpaces(const std::string str) const
{
	std::string spaceless = "";
	for (char c : str)
	{
		if (c != ' ')
		{
			spaceless += c;
		}
	}
	return spaceless;
}

// formPostfix takes in a parameter string in infix notation and
// converts it into postix and returns the resulting string
std::string Postfix::formPostfix(std::string infix)
{
	infix = removeSpaces(infix);
	LinkedStack<char> *stack = new LinkedStack<char>();
	std::string postfix = "";
	char lastChar = '\0';

	if (!balancedParen(infix))
	{
		throw(PrecondViolatedExcep("Parentheses in expression not balanced"));
	}
	//goes through every character in the infix string
	for (char c : infix)
	{
		//if the character is a valid operator
		if (isOperator(c) && (isOperand(lastChar) || lastChar == ')'))
		{
			//safely get the top operator
			char topOp = !stack->isEmpty() ? stack->peek() : '\0';

			//if the current character has higher precedence then the
			//operator at the top of the stack push it.
			if (higherPrecedence(c, topOp))
			{
				stack->push(c);
			}
			else
			{
				//pop off all operators from the stack while they have higher or equal precedence to the current character
				for (char op = topOp; op != '(' && !higherPrecedence(c, op); op = !stack->isEmpty() ? stack->peek() : '\0')
				{
					//don't push parentheses to the postfix string
					if (op != ')')
					{
						postfix += op;
					}
					stack->pop();
				}
				stack->push(c);
			}
		}
		//if the character is a valid operand
		else if (isOperand(c) && (lastChar == '\0' || isOperator(lastChar) || lastChar == '('))
		{
			//add the operand to the postfix string
			postfix += c;
			//keep track of the unique operands
			std::size_t found = seen.find(c);
			if (found == std::string::npos)
			{
				seen += c;
			}
		}
		//if the character is a valid closing parenthese
		else if (c == ')' && (isOperand(lastChar) || lastChar == ')'))
		{
			//pop all characters op until an opening parentheses is found
			for (char op = stack->peek(); op != '('; op = !stack->isEmpty() ? stack->peek() : '(')
			{
				postfix += op;
				op = stack->pop();
			}
		}
		//if the character is a valid opening parenthese
		else if (c == '(' && (isOperator(lastChar) || lastChar == '\0' || lastChar == '('))
		{
			stack->push(c);
		}
		else
		{

			std::cout << isOperator(lastChar) << lastChar << std::endl;
			throw(PrecondViolatedExcep("invalid infix expression"));
		}
		//keep track of the last character
		lastChar = c;
	}

	//after the whole string has been evaluated pop all the characters
	//off the stack to the postfix string
	for (; !stack->isEmpty(); stack->pop())
	{
		if (stack->peek() != '(' && stack->peek() != ')')
		{
			postfix += stack->peek();
		}
	}

	delete stack;
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
	return result;
}

#endif