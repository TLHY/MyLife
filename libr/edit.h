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
	//edit의 기능이 실행
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
	//인자 확인 및 분리 
	//edit의 인자로는 해당 id와 고치고 싶은 정보를 입력받는다...
	//id로 해당 도서의 line을 찾고 그 부분에 대해 새로운 정보를 적는다...?
	//파싱으로 태그와 분리한다.
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