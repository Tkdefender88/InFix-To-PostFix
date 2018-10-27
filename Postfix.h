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

#include "LinkedStack.h"
#include "PrecondViolatedExcep.h"

using namespace std;

class Postfix
{

  private:
	string infix;   // stores infix value
	string postfix; // stores postfix value
	string seen;
	double result; // stores calculation result.

	// Any private Methods should go here
	string formPostfix(string) throw(PrecondViolatedExcep);

	//returns true if the first character has higher precendece than the second
	bool higherPrecedence(const char, const char);
	bool isOperand(const char) const;
	bool isOperator(const char) const;
	bool balancedParen(const string) const;

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
