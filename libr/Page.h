#pragma once
#include "tag_parents.h"

using namespace std;
class Page :public OperationTag {
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main);
};
