#include "tag_parents.h"

// ostream에 대한 left-shift 연산; 출력 함수 사용
std::ostream& operator<<(std::ostream& out, const Tag& tag) {
	tag.Print();
	return out;
}

bool Tag::is_tag(const std::string& str)
{
	if (str.length() < 3) {
		return false;
	}
	if (str.at(0) != ':' || str.at(str.length() - 1) != ':') {
		return false;
	}
	for (unsigned int i = 1; i < str.length() - 1; i++) {
		if (str.at(i) < 'a' || str.at(i) > 'z') {
			return false;
		}
	}
	return true;
}

Tag& Tag::operator<<(std::string str)
{
	if (!_strarg.empty()) {
		_strarg += " ";
	}
	_strarg += str;
	return *this;
}
