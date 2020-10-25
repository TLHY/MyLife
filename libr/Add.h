#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Add{
public:
	vector<string> tags;
	vector<string> title;
	vector<string> author;
	vector<string> publisher;
	vector<string> year;
	void validate();
	fstream& action(fstream& fs);
	void prmParsing(string input);
	int countlines(fstream& fs);

};
void Add::validate(){
	//인자 확인?

}
int Add::countlines(fstream& fs) {
	string str;
	int linenum = 0;
	while (!fs.eof()) {
		getline(fs, str);
		linenum++;
	}
	return linenum;
}
fstream& Add::action(fstream& fs){
	//add의 기능이 실행
	//도서 정보에  title, author, publisher, year 정보 넣기?
	
	fs << countlines(fs)+" ";
	for (int i = 0; i < title.size(); i++) {
		fs << title[i]+" ";
	}
	fs << "\n";
	for (int i = 0; i < author.size(); i++) {
		fs << author[i];
	}
	fs << "\n";
	for (int i = 0; i < title.size(); i++) {
		fs << publisher[i];
	}
	fs << "\n";
	for (int i = 0; i < title.size(); i++) {
		fs << year[i];
	}
	fs.seekp(0, ios::end);
	return fs;
}
void Add::prmParsing(string input) {
	//인자 확인 및 분리
	int i = 0;
	stringstream ssin(input);
	while (ssin.good() && i < input.length()) {
		ssin >> tags[i];
	}
	for (int i = 0; i < tags.size(); i++) {
		if (tags[i] == ":title:") {
			while (tags[i] != ":author:") {
				title.push_back(tags[++i]);
			}
		}
		else if (tags[i] == ":author:") {
			while (tags[i] != ":publisher:") {
				author.push_back(tags[++i]);
			}
		}
		else if (tags[i] == ":publisher:") {
			while (tags[i] != ":year:") {
				publisher.push_back(tags[++i]);
			}
		}
		else if (tags[i] == ":year:") {
			while (i != tags.size()) {
				year.push_back(tags[++i]);
			}
		}
	}
}