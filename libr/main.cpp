#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;
int main() {
	string input = "hello i am eugene";
	
	vector<char> inputs(input.c_str(), input.c_str() + input.size() + 1);

	for (int i = 0; i < inputs.size(); i++) {
		cout << inputs[i] << endl;
	}


	return 0;
}