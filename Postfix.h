/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Postfix Class Definition
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef POSTFIX_H
#define POSTFIX_H

#include <string>
#include <map>

#include "LinkedStack.h"
#include "PrecondViolatedExcep.h"

using namespace std;

class Postfix
{

  private:
	string infix;				   // stores infix value
	string postfix;				   // stores postfix value
	string seen;				   // stores all the unique idetifiers seen
	double result;				   // stores calculation result.
	std::map<char, double> values; // stores what each idetifier holds

	// Any private Methods should go here
	string formPostfix(string);

	//returns true if the first character has higher precendece than the second
	bool higherPrecedence(const char, const char);

	//isOperand takes in a character parameter 'c' and returns true if 'c'
	//is with in the range of the normal alphabet capital or lowercase,
	//otherwise false.
	bool isOperand(const char) const;

	// isOperator takes in a character parameter 'c' and returns true if
	// 'c' is with an operator, otherwise false. Operators are defined
	// as the following characters +, -, *, /, ^, (, )
	bool isOperator(const char) const;

	//balancedParen checks to see if a given string has balanced parentheses
	//if all the parentheses match then it returns true otherwise false.
	bool balancedParen(const string) const;

	// removeSpaces takes in a string and removes all space ' ' characters
	// from it and returns the resulting string
	string removeSpaces(const string) const;

	//caclReuslt calulates the result of the infix expression and returns the result.
	//throws PrecondViolatedExcep error
	double calcResult() const;

	//getValues prompts the user for what each identifier holds
	void getValues();

  public:
	// Constructors

	/**
 * Constructor to take astring representation of an 
 * algebraic expression 
 */
	Postfix(string infix);

	// Other public methods should go here

	/**
 * Return a string representation of the 
 * algebraic expression in infix notation
 */
	string getInfix();

	/**
 * Return a string representation of the 
 * algebraic expresion in postfix notation
 */
	string getPostfix();

	/**
 * Returns a double representing the 
 * evaluation of the algebraic expression
 */
	double getResult();
};

#endif