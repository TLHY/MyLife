#include "Edit.h"
#include "MainPrompt.h"
#include "BookList.h"

Tag* Edit::copy() const {
	return new Edit(*this);
}
void Edit::Print() const {
	cout << ":edit: " << _strarg << endl;
}
void Edit::Validate() {
	//단순 문법 규칙확인입니다.
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
void Edit::Operate(MainPrompt& main) {
	main.entire_books().EditOP(&main.input_bundle());
}