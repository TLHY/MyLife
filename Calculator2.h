#pragma once
#include "Calculator.h"
class Calculator2 :public Calculator {
public:
	int getPriority2(char op);
	int calculate2(string str, int a);
	string convertExpression2(string str);
	void process2();
};
