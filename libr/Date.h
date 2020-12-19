#pragma once
#include "exceptions.h"
using namespace std;
class Date :public BookTag {
public:
	Tag* copy() const;
	string get_Date();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};