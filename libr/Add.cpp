#include "Add.h"
#include "MainPrompt.h"

Tag* Add::copy() const {
	return new Add(*this);
}
void Add::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Add::Print() const {
	cout << ":add: " << _strarg << endl;
}
void Add::Operate(MainPrompt& main) {
	main.entire_books().AddOP(&main.input_bundle());
}
