#include "Del.h"
#include "MainPrompt.h"
#include "BookList.h"

Tag* Del::copy() const {
	return new Del(*this);
}
void Del::Validate() {
	//��Ģ Ȯ�� ���⼭ ���� �±׵��� ��Ģ�� ��� �¾Ҵٰ� �����ϰڽ��ϴ�.
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	//id�� �ƴϸ� ������Ģx
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