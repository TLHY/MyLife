#pragma once
#include <iostream>
#include <vector>
#include "tag_parents.h"
#include <string>

using namespace std;
class Edit :public OperationTag {
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
