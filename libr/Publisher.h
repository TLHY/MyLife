#pragma once
#include <iostream>
#include <vector>
#include "exceptions.h"

using namespace std;
class Publisher :public BookTag {
public:
	Tag* copy() const;
	string get_Publisher();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
