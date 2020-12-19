#include "Date.h"
#include <regex>

Tag* Date::copy() const {
	return new Date(*this);
}
string Date::get_Date() {
	return this->strarg();
}
void Date::Validate() {
	/*���� ���� : ���� d�� �ƹ� ���ڿ� �����Ǵ� ������ ��, ���������� �ùٸ� ���ǳ⵵�� ���� �װ��� ���Ŀ� �����ϴ� ���ڿ��Դϴ� :
		1ddd
		200d
		201d
		2020
		*/
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
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	if (_intarg > 2020 || _intarg < 1000) {
		throw InvalidArgument(this);
	}
	
}
void Date::Print() const {
	std::cout << ":date: " << _strarg << endl;;
}
bool Date::Match(const BookTag* search) const {
	if (typeid(*(search)) == typeid(Date)) {
		std::string my_arg = _strarg;
		std::string search_arg = search->strarg();
		// ���ڿ��� ��� ���ڷ� ������ �� �˻�
		int my_num = stoi(my_arg);
		int search_num = stoi(search_arg);
		return my_num == search_num;
	}
	else return false;
}


