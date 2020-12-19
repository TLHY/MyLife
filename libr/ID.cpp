#include "ID.h"
#include <algorithm>
Tag* ID::copy() const {
	return new ID(*this);
}
string ID::get_ID() {
	return this->strarg();
}
void ID::Validate() {
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
void ID::Print() const {
	std::cout << ":id: " << _strarg << endl;;
}
bool ID::Match(const BookTag* search) const {
	
	if (typeid(*(search)) == typeid(ID)) {
		std::string my_arg = _strarg;
		std::string search_arg = search->strarg();
		// 문자열을 모두 숫자로 변경한 뒤 검사
		int my_num = stoi(my_arg);
		int search_num = stoi(search_arg);
		return my_num == search_num;
	}
	else return false;
}