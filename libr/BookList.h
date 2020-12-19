#pragma once
#include "Book.h"

class TagBudle;

using namespace std;

class BookList {
public:
	vector<Book*> book;
	vector<TagBundle*> filters;

	//생성자 
	BookList() {};
	BookList(string path);

	//검색하기
	BookList search(TagBundle filters);

	void AddOP(TagBundle* input);

	void EditOP(TagBundle* input);

	void DelOP(TagBundle* input);

	void PageOP(TagBundle* input);

	void ClearOP(TagBundle* input);

	//도서목록찾기
	vector<Book> IdSearch(int ID);

	//출력하기
	void Print(int n);

	//파괴자 
};
