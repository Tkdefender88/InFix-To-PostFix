/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Algebraic infix expression evaluator using postfix and a stack
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#include <iostream>
#include <string>

#include "Postfix.h"

using namespace std;

int main()
{
	string infix = "";
	cout << "Please give infix expression: ";
	getline(cin, infix);

	Postfix pfix = Postfix(infix);

	cout << "Infix: " << pfix.getInfix() << endl;
	cout << "Postfix: " << pfix.getPostfix() << endl;
	cout << "Getting values: " << endl;
	cout << "Result: " << pfix.getResult() << endl;

	return 0;

} // end main()