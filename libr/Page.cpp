#include "Page.h"
#include "MainPrompt.h"

Tag* Page::copy() const {
	return new Page(*this);
}
void Page::Validate() {
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	for (int i = 0; i < _strarg.length(); i++) {
		if (_strarg.at(i) > '9' || _strarg.at(i) < '0') {
			throw InvalidArgument(this);
		}
	}
	try {
		int a = stoi(_strarg);
		_intarg = a;
	}
	catch (std::out_of_range&) {
		throw InvalidArgument((Tag*)this);
	}
}
void Page::Print() const {
	cout << ":page: " << _strarg << endl;
}
void Page::Operate(MainPrompt& main) {
	main.searched_books().PageOP(&main.input_bundle());
}