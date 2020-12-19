#pragma once
#include "Book.h"

class TagBudle;

using namespace std;

class BookList {
public:
	vector<Book*> book;
	vector<TagBundle*> filters;

	//������ 
	BookList() {};
	BookList(string path);

	//�˻��ϱ�
	BookList search(TagBundle filters);

	void AddOP(TagBundle* input);

	void EditOP(TagBundle* input);

	void DelOP(TagBundle* input);

	void PageOP(TagBundle* input);

	void ClearOP(TagBundle* input);

	//�������ã��
	vector<Book> IdSearch(int ID);

	//����ϱ�
	void Print(int n);

	//�ı��� 
};
