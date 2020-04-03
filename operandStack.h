#pragma once
class operandStack
{
private:
	int top = -1;
	int data[100] = {};
public:
	void push(int c) {
		data[++top] = c;
	}
	int pop() {
		return data[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	int peek() {
		return data[top];
	}
	int size() {
		return top + 1;
	}

};