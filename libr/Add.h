#pragma once
#include "tag_parents.h"

class Add :public OperationTag {
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
