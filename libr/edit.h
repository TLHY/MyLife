#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class edit{
public:
	void validate();
	void action(fstream& fs);
	void prmParsing(string input);
	int linenum;
	vector<string>tags;
	vector<string> tags;
	vector<string> title;
	vector<string> author;
	vector<string> publisher;
	vector<string> year;
};

void edit::validate(){


}

void edit::action(fstream& fs){
	//edit�� ����� ����
	string str;
	int fline;
	while (getline(fs, str) && !fs.eof()) {
		fline++;
		if (linenum==fline) {
			str.find()....?
		}
		else {
			fs << str << endl;
		}
	}


}

void edit::prmParsing(string input){
	//���� Ȯ�� �� �и� 
	//edit�� ���ڷδ� �ش� id�� ��ġ�� ���� ������ �Է¹޴´�...
	//id�� �ش� ������ line�� ã�� �� �κп� ���� ���ο� ������ ���´�...?
	//�Ľ����� �±׿� �и��Ѵ�.
	int i = 0;
	stringstream ssin(input);
	while (ssin.good() && i < input.length()) {
		ssin >> tags[i];
	}
	for (int i = 0; i < tags.size(); i++) {
		if (tags[i] == ":title:") {
			while (tags[i] != ":author:" || tags[i] != ":publisher:" || tags[i] != ":year:") {
				title.push_back(tags[++i]);
			}
		}else if (tags[i] == ":author:") {
			while (tags[i] != ":title:" || tags[i] != ":publisher:" || tags[i] != ":year:") {
				author.push_back(tags[++i]);
			}
		}else if (tags[i] == ":publisher:") {
			while (tags[i] != ":title:" || tags[i] != ":author:" || tags[i] != ":year:") {
				publisher.push_back(tags[++i]);
			}
		}else if (tags[i] == ":year:") {
			while (tags[i] != ":author:" || tags[i] != ":publisher:" || tags[i] != ":title:") {
				year.push_back(tags[++i]);
			}
		}
		else {
			linenum = stoi(tags[i]);
		}
	}
}