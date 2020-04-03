#include "Calculator2.h"
using namespace std;
int Calculator2::getPriority2(char op) {
	if (op == '*' || op == '/') return 2;
	else return this->getPriority(op);
}
bool isNumber2(char c) {
	return (c >= '0' && c <= '9');
}
int Calculator2::calculate2(string str,int count) {
	operandStack numbers;
	string temp;
	int result = 0;
	for (int i = 0; i < 100; i++) {
		if (str[i] == '\0') {
			break;
		}
		else if ((str[i] == '-'&&(i-1)<0) || (str[i] == '-'&& isNumber2(str[i + 1]))) {
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
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			int num2 = numbers.pop();
			int num1 = numbers.pop();
			
			switch (str[i]) {
			case '+': {
				result = num1 + num2;
				break;
			}
			case '-': {
				result = num1 - num2;
				break;
			}
			case '*': {
				result = num1 * num2;
				break;
			}
			case '/': {
				result = num1 / num2;
				break;
			}
			}
			if (count != 0) {
				cout << "°ýÈ£ Ãâ·Â: ( " << num1 << " "<<str[i] <<" "<< num2 << " ) = " << result << endl;
				count--;
			}
			numbers.push(result);
		}
		else if (str[i] == ' ') {
			continue;
		}
		else if (str[i] == '('||str[i]==')') {
			continue;
		}
		
		else {
			 for(int j = i; j < 100; j++) {
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

string Calculator2::convertExpression2(string str) {
	
	operatorStack oprt;
	operandStack combine;
	operandStack reverse;
	string newstring;
	string templine;
	for (int i = 0; i < 100; i++) {
		if (str[i] == '\0') {
			break;
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
		else if (str[i] == '-'&&(i-1)<0) {
			newstring += str[i];
			continue;
		}
		else if (str[i] == '-' &&str[i-1]!=')' &&str[i - 1] != '(' &&!isNumber2(str[i - 1]) && isNumber2(str[i + 1])) {
			newstring += str[i];
			continue;
		}
		else if (isNumber2(str[i])) {
			for (int j = i; j < 100; j++) {
				if (isNumber2(str[j])) {
					templine += str[j];
				}
				else {
					i = j - 1;
					break;
				}
			}
			newstring += templine + " ";
			templine = "";
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if (oprt.isEmpty() || getPriority2(oprt.peek()) == 3) {
				oprt.push(str[i]);
			}
			else {
				char c = oprt.peek();
				int currentOprt = getPriority2(c);
				int newOprt = getPriority2(str[i]);
				if (currentOprt >newOprt) {
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
void Calculator2::process2() {
	string a = getExpression();
	int count = parentheseCount(a);
	string postfix = convertExpression2(a);
	int result = calculate2(postfix,count);
	cout<<"ÃÑ °è»ê °á°ú: "<<result <<endl;
}