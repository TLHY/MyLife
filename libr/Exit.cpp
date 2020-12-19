#include "Exit.h"
#include "MainPrompt.h"
#include "exceptions.h"

Tag* Exit::copy() const {
	return new Exit(*this);
}
void Exit::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Exit::Print() const {
	cout << ":exit:" << endl;
}
void Exit::Operate(MainPrompt& main) {
	throw ProgramTerminated();
}
