#pragma once
#include <iostream>
#include "operatorStack.h"
#include <string>
#include "operandStack.h"
#include <cstdio>
#include<cstdlib>
using namespace std;
class Calculator {
public:
	string convertExpression(string str);
	void process();
	int getPriority(char op);
	string getExpression();
	int calculate(string str, int a);
	void parentheseCalculate(string str, int i);
	int parentheseCount(string str);
};
