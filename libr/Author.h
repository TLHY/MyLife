#pragma once
#include "exceptions.h"
using namespace std;
class Author :public BookTag {
public:
	Tag* copy() const;
	string get_Author();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};