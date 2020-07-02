#include "Calculator.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Calculates the result of the two given integers with the operation
// Params: int x - the first operand, int y - the second operand, char func - the operation
// Returns: the result of whichever operation was passed in
int Calculator::calculate(int x, int y, char func) {
	switch (func) {
	case '+':
		return x + y;
	case '*':
		return x * y;
	case '-':
		return x - y;
	case '/':
		if (y == 0) { throw "Cannot divide by 0"; }
		return x / y;
	case '%':
		return x % y;
	default:
		return 0;
	}
}

// Parses the string taken from the user by deleting the whitespace if any, then passes the valid characters into an array
// Params: string expr - the string input taken from the user
// Returns: vector<char> expression - a char vector of the expression taken from the user without whitespace
vector<char> Calculator::parseExpression(string expr) {

	expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
	vector<char> expression;
	for (int i = 0; i < expr.size(); i++) {
		if ((expr.at(i) >= '0' && expr.at(i) <= '9') || expr.at(i) == '+' || expr.at(i) == '*' || 
			expr.at(i) == '-' || expr.at(i) == '/' || expr.at(i) == '%' || expr.at(i) == '(' || expr.at(i) == ')') {
			expression.push_back(expr.at(i));
		}
	}
	return expression;
}

// Prints the vector in a readable way. Used for debugging
// Params: vector<char> expression - the vector to be printed
// Returns: n/a
void Calculator::printExpression(vector<char> &expression) {
	for (auto i = expression.begin(); i != expression.end(); i++) {
		cout << *i << "";
	}
	cout << endl;
}

// A recursive function that solves the equation given. When the function is called on the vector, it checks to see if either of the first two 
// operands are a left parenthesis, if not, then it solves the calculation of the first two operands, removes them from the vector, then inserts 
// the result of the calculation. If either of the first two operands are a left parenthesis, the function separates the equation in the parenthesis
// and solves for that section before inserting the result back into the vector.
// Params: vector<char> equation - the vector of the expression that is recursively solved
// Returns: equation.at(0) - the computed result of the entire equation
int Calculator::getResult(vector<char> &equation) {
	int x, y;
	char op;
	if (equation.size() == 1) {
		return equation.at(0)-'0';
	} else {
		if (equation.at(0) == '(') {
			int i = 0;
			vector<char> parenExpr;
			while (equation.at(i + 1) != ')') {
				parenExpr.push_back(equation[++i]);
			}
			equation.erase(equation.begin(), equation.begin() + i + 2);
			equation.insert(equation.begin(), getResult(parenExpr) + '0');
			return getResult(equation);
		}
		else if (equation.at(2) == '(') {
			int i = 2;
			vector<char> parenExpr;
			while (equation.at(i + 1) != ')') {
				parenExpr.push_back(equation[++i]);
			}
			equation.erase(equation.begin() + 2, equation.begin() + i + 2);
			equation.insert(equation.begin() + 2, getResult(parenExpr) + '0');
			return getResult(equation);
		}
		else {
			x = equation.at(0) - '0';
			y = equation.at(2) - '0';
			op = equation.at(1);
			equation.erase(equation.begin(), equation.begin() + 3);
			equation.insert(equation.begin(), calculate(x, y, op) + '0');
			return getResult(equation);
		}
	}
}


/*
Future Work
1. Solve with Larger Integers
Since the operands are stored as chars, they are limited to single digits. In order to have integers with multiple digits, I would 
need to find a way to store them as integers or doubles. Then figure out a way to integrete the operators with the correct operands. 
This could also help with large totals since some of the answers are too large to be stored as a char
2. Division 
Similar to the above issue, since the vector is a char vector, it cannot store doubles. This could be potentially solved by storing
the result separately or by having a double vector used
3. Consildation
In the getResult function, the code for the left paren being the first operand and the code for the left paren being the second operand
is identical save for the starting position for the erase function. This could be consildated down to one if statement with the right variable
4. Flexibility 
Some of the values in getResult are hardcoded to look at specific instances of the vector. Maybe this could be modified so it's more dynamic
in the future
*/