#pragma once
class operatorStack
{
private:
	int top = -1;
	char data[100] = {};

public:
	void push(char c) {
		data[++top] = c;
		
	}
	char pop() {
		return data[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	char peek() {
		return data[top];
	}
	
}; 
