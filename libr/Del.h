#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
class Del {
public:
	void validate();
	int input;
	void action(fstream& fs,string input);
	int prmParsing(string input);

};
void Del::validate(){


}

void Del::action(fstream& fs,string input){
	//del�� ����� ����
	string str;
	int linenum = 0;
	while (getline(fs, str) && !fs.eof()) {
		if (linenum == stoi(input)) {
			continue;
		}
		else {
			fs << str << endl;
		}
	}
}
void Del::prmParsing(string input) {
	//���� Ȯ�� �� �и�
	//del�� ��� �ĺ���ȣ�� ����Ѵٰ� �����Ѵ�..
	//...?
}
