#include <iostream>
#include <vector>
#include <string>
#include "Calculator.h"

using namespace std;

// Driver function 
int main() {
	Calculator myCalc;

	cout << "******* Simple Calculator*******\n";
	cout << "Enter in an equation using +, *, -, or % with digits 0-9\n";
	cout << "Division (/)  returns the floor value of the quotient\n";
	cout << "Enter \"q\" to quit\n\n";

	while (true) {
		string expression;
		cout << "Please enter the expression you would like to solve: ";
		getline(cin, expression);
		if (expression == "q") { exit(0); }
		vector<char> equation = myCalc.parseExpression(expression);
		try {
			cout << "Result is " << myCalc.getResult(equation) << endl;
			equation.clear();
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
		catch (const out_of_range) {
			cerr << "Please enter a digit (0-9) after an operator" << endl;
		}
		catch (...) {
			cerr << "There has been an error" << endl;
		}
	}

	return 0;
}