#pragma once
#include "exceptions.h"
using namespace std;

class Title :public BookTag {
public:
	string get_Title();
	Tag* copy() const;
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
