#pragma once
#include "exceptions.h"
using namespace std;
class ID :public BookTag {
public:
	Tag* copy() const;
	string get_ID();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
