#include "Clear.h"
#include "MainPrompt.h"

Tag* Clear::copy() const {
	return new Clear(*this);
}
void Clear::Print() const {
	cout << ":clear:" << endl;
}
void Clear::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Clear::Operate(MainPrompt& main) {
	main.searched_books().ClearOP(&main.input_bundle());
}