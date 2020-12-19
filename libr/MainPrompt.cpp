#include "MainPrompt.h"
#include "book_tags.h"
#include "operation_tags.h"

Tag* MainPrompt::GetTag(const std::string str) const
{
	if (str == ":title:") {
		return new Title();
	}
	else if (str == ":author:") {
		return new Author();
	}
	else if (str == ":publisher:") {
		return new Publisher();
	}
	else if (str == ":date:") {
		return new Date();
	}
	else if (str == ":id:") {
		return new ID();
	}
	else if (str == ":add:") {
		return new Add();
	}
	else if (str == ":edit:") {
		return new Edit();
	}
	else if (str == ":del:") {
		return new Del();
	}
	else if (str == ":clear:") {
		return new Clear();
	}
	else if (str == ":exit:") {
		return new Exit();
	}
	else if (str == ":page:") {
		return new Page();
	}
	else if (str == ":help:") {
		return new Help();
	}
	throw InvalidTag(str.c_str());
}

MainPrompt::MainPrompt()
{
	_file = File("./BookShelf.txt");
	vector<Book*> books;
	books = _file.import_book_list();
	_entire_books.book = books;
}

BookList& MainPrompt::entire_books()
{
	return _entire_books;
}

BookList& MainPrompt::searched_books()
{
	return _searched_books;
}

std::string& MainPrompt::raw_input()
{
	return _raw_input;
}

TagBundle& MainPrompt::input_bundle()
{
	return _input_bundle;
}

void MainPrompt::Prompt()
{
	// ������Ʈ ���
	std::cout << "\n*********************************************************"<<endl;                                                           
	std::cout << "*���� ������ �˻��ϰų� �����ϱ� ���� ������ �Է��ϼ���.*\n" << "*********************************************************" << "\n\nBooking:������Ʈ>";
	
	std::getline(std::cin, _raw_input);
	cout << "\n*********************************************************\n" << endl;

	
	// �Է� ���ڿ��� ���� ��Ģ �˻�
	if (_raw_input.empty()) {
		throw InvalidInput(_raw_input.c_str());
	}
	if (_raw_input.length() > 500) {
		throw InvalidInput(_raw_input.c_str());
	}
	if (_raw_input.at(0) == ' ' || _raw_input.at(_raw_input.length() - 1) == ' ') {
		throw InvalidInput(_raw_input.c_str());
	}
	if (_raw_input.length() >= 2) {
		for (unsigned int i = 0; i < _raw_input.length(); i++) {
			if (_raw_input.at(i) < ' ' || _raw_input.at(i) > '~') {
				throw InvalidInput(_raw_input.c_str());
			}
			if (i > 0) {
				if (_raw_input.at(i - 1) == ' ' && _raw_input.at(i) == ' ') {
					throw InvalidInput(_raw_input.c_str());
				}
			}
		}
	}
	int tag_found = 0;
	std::stringstream ss(_raw_input);
	std::string token;
	while (ss >> token) {
		tag_found += Tag::is_tag(token);
	}
	if (tag_found > 10) {
		throw InvalidInput(_raw_input.c_str());
	}

	// ������ ��ġ�� :title: ����
	ss.str(_raw_input);
	ss.clear();
	if (!tag_found) {
		ss.str(_raw_input);
		ss.clear();
		_raw_input = ":title: " + _raw_input + " :";
		while (ss >> token) {
			token = ":title: " + token + " :";
			if (_raw_input.find(token) == std::string::npos) {
				_raw_input = _raw_input.substr(0, _raw_input.length() - 1) + token;
			}
		}
		_raw_input = _raw_input.substr(0, _raw_input.length() - 2);
	}

	// ���ڿ� -> �±� ����
	ss.str(_raw_input);
	ss.clear();
	_input_bundle = TagBundle();
	Tag* current_tag = nullptr;
	while (ss >> token) {
		if (Tag::is_tag(token)) {
			if (current_tag != nullptr) {
				_input_bundle.tags.push_back(current_tag);
			}
			current_tag = GetTag(token);
		}
		else {
			if (current_tag == nullptr) {
				throw InvalidInput(_raw_input.c_str());
			}
			(*current_tag) << token;
		}
	}
	if (current_tag != nullptr) {
		_input_bundle.tags.push_back(current_tag);
	}

	// �±� ������ ��Ģ �˻�
	_input_bundle.Validate();
	if (_input_bundle.tags.empty()) {	// �±� ������ ����ִ� ���
		throw InvalidInput(_raw_input.c_str());
	}
	TagBundle operation_tags = _input_bundle.GetTagByType<OperationTag>();
	TagBundle book_tags = _input_bundle.GetTagByType<BookTag>();
	if (operation_tags.tags.size() > 1) {	// ��� �±װ� ���� ���� ���
		throw MultipleOperationTags();
	}
	else if (operation_tags.tags.size() == 1) {	// ��� �±װ� �� ���� ���
		const type_info& operation_type = typeid(*(operation_tags.tags.at(0)));
		OperationTag* operation_tag = (OperationTag*)operation_tags.tags.at(0);
		int title_found = _input_bundle.GetTagByType<Title>().tags.size();
		int author_found = _input_bundle.GetTagByType<Author>().tags.size();
		int publisher_found = _input_bundle.GetTagByType<Publisher>().tags.size();
		int date_found = _input_bundle.GetTagByType<Date>().tags.size();
		if (operation_type == typeid(Add)) {   // :add:�� ���� �� �ٸ� ���� �±װ� ���ų� �ߺ� ���� ���
			if (!(title_found == 1 && author_found == 1 && publisher_found == 1 && date_found == 1)) {
				throw NeedEveryBookTag();
			}
		}
		else if (operation_type == typeid(Edit)) {   // :edit:�� ���� ��
			if (!(title_found == 1 || author_found == 1 || publisher_found == 1 || date_found == 1)) {   // �ٸ� ���� �±װ� ���ų� �ߺ� ���� ���
				throw NeedOneOrMoreBookTag();
			}
			_entire_books.IdSearch(operation_tags.tags.at(0)->intarg());   // ������ id�� �������� �ʴ� ���
		}
		else {
			if (_input_bundle.tags.size() != 1) {
				throw MeaninglessBookTag();
			}
			if (operation_type == typeid(Del)) {	// :del:�� ���� �� ������ id�� �������� �ʴ� ���
				_entire_books.IdSearch(operation_tags.tags.at(0)->intarg());
			}
			else if (operation_type == typeid(Page)) {	// :page:�� ���� ��
				if (_searched_books.book.size() == 0)	// ���� �˻� ����� �������� �ʴ� ���
					throw NotResult();
				else if (_input_bundle.tags[0]->intarg() < 1 || _input_bundle.tags[0]->intarg() > _searched_books.book.size() / 10 + 1)	// �������� �������� �ʴ� ���
					throw PageNotFound(&Page());
			}
			else if (operation_type == typeid(Clear)) {	// :clear:�� ���� ��
				if (_searched_books.book.size() == 0)	// ���� �˻� ����� �������� �ʴ� ���
					throw NotResult();
			}
		}
	}
	TagBundle id_tags = book_tags.GetTagByType<ID>();
	for (unsigned int i = 0; i < id_tags.tags.size(); i++) {	// :id:�� ���� �� ������ id�� �������� �ʴ� ���
		_entire_books.IdSearch(id_tags.tags.at(i)->intarg());
	}



	// �Է¿� ���� ó��
	if (operation_tags.tags.empty()) {
		if (_searched_books.book.size() == 0)
			_searched_books = _entire_books.search(_input_bundle);
		else
			_searched_books = _searched_books.search(_input_bundle);
	}
	else {
		((OperationTag*)operation_tags.tags.at(0))->Operate(*this);
	}
}