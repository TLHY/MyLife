#include "Calculator.h"
using namespace std;
string Calculator::getExpression() {
	cout << "Input Expression: ";
	string expression;
	getline(cin, expression);
	return expression;
}
int Calculator::parentheseCount(string str) {
	int count = 0;
	for (int i = 0; i < 100; i++) {
		if (str[i] == '(') {
			count++;
		}
		else if (str[i] == '\0')break;
	}
	return count;
}
int Calculator::getPriority(char op) {
	if (op == '+' || op == '-')return 1;
	else if (op == '(' || op == ')')return 3;
	else { cout << "Unknown Operator" << endl; return -1; }
}
bool isNumber(char c) {
	return (c >= '0' && c <= '9');
}
void Calculator::parentheseCalculate(string str, int i) {
	operandStack number;
	string temp;
	int result = 0;
	for (int j = i; i < 100; i++) {
		if (str[i] == ')') {
			cout << ') =';
			number.pop();
			break;
		}
		else if (str[i] == '+' || str[i] == '-') {
			int num2 = number.pop();
			int num1 = number.pop();
			switch (str[i]) {
				cout << num1 << str[i] << num2;
			case '+': {
				result = num1 + num2; 
				break; 
			}
			case '-': {
				result = num1 - num2; 
				break; 
			}
			}
			number.push(result);
		}
		else if (str[i] == ' ')continue;
		else {
			for (int j = i; j < 100; j++) {
				if (str[j] >= '0' && str[j] <= '9') {
					temp += str[j];
				}
				else
				{
					i = j - 1;
					break;
				}
			}
			int a = stoi(temp);
			number.push(a);
			temp = "";
		}
	}
}
int Calculator::calculate(string str, int count) {
	operandStack numbers;
	string temp;
	int result = 0;
	for (int i = 0; i < 100; i++) {
		if (str[i] == '\0') {
			break;
		}
		else if ((str[i] == '-' && (i - 1) < 0) || (str[i] == '-' && isNumber(str[i + 1]))) {
			temp += '-';
			for (int j = i + 1; j < 100; j++) {
				if (str[j] >= '0' && str[j] <= '9') {
					temp += str[j];
				}
				else
				{
					i = j - 1;
					break;
				}
			}
			int a = stoi(temp);
			numbers.push(a);
			temp = "";
			continue;
		}
		else if (str[i] == '+' || str[i] == '-') {
			int num2 = numbers.pop();
			int num1 = numbers.pop();
			switch (str[i]) {
			case '+':result = num1 + num2; break;
			case '-':result = num1 - num2; break;
			}
			if (count != 0) {
				cout << "°ýÈ£ Ãâ·Â: ( " << num1 << " " << str[i] << " " << num2 << " ) = " << result << endl;
				count--;
			}
			numbers.push(result);
		}
		else if (str[i] == ' ')continue;
		else {
			for (int j = i; j < 100; j++) {
				if (str[j] >= '0' && str[j] <= '9') {
					temp += str[j];
				}
				else
				{
					i = j - 1;
					break;
				}
			}
			int a = stoi(temp);
			numbers.push(a);
			temp = "";
		}
	}
	return numbers.pop();
}
string Calculator::convertExpression(string str) {
	operatorStack oprt;
	operandStack combine;
	operandStack reverse;
	string newstring;
	string templine;
	int digits = 1;
	for (int i = 0; i < 100; i++) {
		if (str[i] == '\0') {
			break;
		}
		else if (str[i] == '*' || str[i] == '/') {
			cout << "Operator Error" << endl;
			cout << "Re-Enter Operator" << endl;
			cin >> str[i];
			i--;
		}
		else if (str[i] == '(') {
			oprt.push('(');
		}
		else if (str[i] == ')') {
			while (oprt.peek() != '(') {
				newstring += oprt.pop();
				newstring += " ";
			}
			oprt.pop();
		}
		else if (str[i] == '-' && (i - 1) < 0) {
			newstring += str[i];
			continue;
		}
		else if (str[i] == '-' && str[i - 1] != ')' && str[i - 1] != '(' && !isNumber(str[i - 1]) && isNumber(str[i + 1])) {
			newstring += str[i];
			continue;
		}
		else if (isNumber(str[i])) {
			for (int j = i; j < 100; j++) {
				if (isNumber(str[j])) {
					templine += str[j];
				}
				else {
					i = j - 1;
					break;
				}
			}
			newstring += templine;
			newstring += " ";
			templine = "";
		}
		else if (str[i] == '+' || str[i] == '-') {
			if (oprt.isEmpty() || getPriority(oprt.peek()) == 3) {
				oprt.push(str[i]);
			}
			else {
				char c = oprt.peek();
				int currentOprt = getPriority(c);
				int newOprt = getPriority(str[i]);
				if (currentOprt > newOprt) {
					newstring += oprt.pop();
					newstring += " ";
					oprt.push(str[i]);
				}
				else {
					oprt.push(str[i]);
				}
			}
		}
	}
	while (!oprt.isEmpty()) {
		newstring += oprt.pop();
		newstring += " ";
	}
	return newstring;
}
void Calculator::process() {
	string a = getExpression();
	int count = parentheseCount(a);
	string postfix = convertExpression(a);
	int result = calculate(postfix,count);
	cout << "ÃÑ °è»ê °á°ú: " << result << endl;
}
