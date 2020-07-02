#ifndef Calculator_H
#define Calculator_H

#include <vector>
#include <string>

class Calculator {
	public:
		int calculate(int x, int y, char func);
		std::vector<char> parseExpression(std::string expr);
		void printExpression(std::vector<char> &expression);
		int getResult(std::vector<char> &equation);
};

#endif