#include "Del.h"
#include "MainPrompt.h"
#include "BookList.h"

Tag* Del::copy() const {
	return new Del(*this);
}
void Del::Validate() {
	//규칙 확인 여기서 도서 태그들은 규칙이 모두 맞았다고 가정하겠습니다.
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	//id가 아니면 문법규칙x
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
void Del::Print() const {
	cout << ":del: " << _strarg << endl;
}
void Del::Operate(MainPrompt& main) {
	main.entire_books().DelOP(&main.input_bundle());
}