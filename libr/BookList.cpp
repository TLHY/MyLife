#include "BookList.h"
#include <typeinfo>
#include <string>
#include "FileIO.h"
#include "book_tags.h"
#include "operation_tags.h"
#include "exceptions.h"
#include "Subprompt.h"
#include "TagBundle.h"
#include "MainPrompt.h"

BookList::BookList(string path) : BookList() {
	for (int i = 0; i < book.size(); i++) {
		book[i]->get_ID();
		book[i]->get_Title();
		book[i]->get_Author();
		book[i]->get_Publisher();
		book[i]->get_Date();
	}
}

BookList BookList::search(TagBundle filters) {
    BookList* nbooks = new BookList;
    vector<int> index;
    int hcount = 0;
    int page = 0;
    int n = 0;
    for (unsigned int i = 0; i < this->filters.size(); i++) {
        TagBundle* filter = this->filters.at(i);
        nbooks->filters.push_back(new TagBundle(*filter));
        cout << "== = 검색 조건 == =\n" << endl;
        cout << *filter << endl;
    }
    nbooks->filters.push_back(new TagBundle(filters));
    cout << "== = 검색 조건 == =\n" << endl;
    cout << filters << endl;

    for (unsigned int i = 0; i < book.size(); i++) {
        index.push_back(book.at(i)->Match(filters));
        if (hcount < index.at(i))
            hcount = index.at(i);
    }
    for (unsigned int j = hcount; j > 0; j--) {
        for (unsigned int i = 0; i < book.size(); i++) {
            if (index[i] == j) {
                Book* temps = new Book;
                temps->set_ID(book[i]->get_ID());
                temps->set_Title(book[i]->get_Title());
                temps->set_Author(book[i]->get_Author());
                temps->set_Publisher(book[i]->get_Publisher());
                temps->set_Date(book[i]->get_Date());
                nbooks->book.push_back(temps);
                n++;
            }
        }
    }
    nbooks->Print(1);
    return *nbooks;
}

void BookList::AddOP(TagBundle* input) {
	if (book.size() > 499) {
		throw OverLineAdd(book.size());
	}
	Book* newBook = new Book;
	cout << endl;
	string s;
	int emptyIndex = 0;
	int k = 0;
	int insertNum = 1;
	for (int i = 0; i < book.size(); i++) {
		if (book.at(i)->get_ID() == "EMPTY") {
			emptyIndex = i;
			break;
		}
	}
	for (int i = 0; i < book.size(); i++) {
		for (int j = 0; j < book.size(); j++) {
			if (insertNum == stoi(book.at(j)->get_ID())) {
				if (book.at(j)->get_ID() == "EMPTY") {
					continue;
				}
				insertNum++;
			}
		}
	}
	for (int i = 0; i < input->tags.size(); i++) {
		if (typeid(*(input->tags[i])) == typeid(Title)) {
			newBook->set_Title(input->tags[i]->strarg());
		}
		else if (typeid(*(input->tags[i])) == typeid(Author)) {
			newBook->set_Author(input->tags[i]->strarg());
		}
		else if (typeid(*(input->tags[i])) == typeid(Publisher)) {
			newBook->set_Publisher(input->tags[i]->strarg());
		}
		else if (typeid(*(input->tags[i])) == typeid(Date)) {
			newBook->set_Date(input->tags[i]->strarg());
		}
	}
	cout << "#\t| 도서명\t| 저자명 \t| 출판사명 \t| 출판년도 \t\n" << endl;
	if (emptyIndex == 0 && book.size() == 0) {
		newBook->set_ID("0");
		newBook->Print();
	}
	else if (emptyIndex == 0 && book.size() != 0) {
		newBook->set_ID(to_string(insertNum));
		newBook->Print();
	}
	else if (emptyIndex != 0) {
		newBook->set_ID(to_string(insertNum));
		newBook->Print();
	}
	cout << "\n" << endl;
	SubPrompt sp = SubPrompt("도서 정보를 저장하시겠습니까 ? (Y / N) >");
	if(sp.is_real()){
		if (emptyIndex == 0 && book.size() == 0) {
			book.push_back(newBook);
		}
		else if (emptyIndex == 0 && book.size() != 0) {
			book.push_back(newBook);
		}
		else if (emptyIndex != 0) {
			book.at(emptyIndex) = newBook;
		}
		File tempfile = File("./BookShelf.txt");
		tempfile.export_book_unit(book);
	}	
}
void BookList::EditOP(TagBundle* input) {
	if (book.size() > 500) {
		throw OverLineAdd(book.size());
	}
	Book* editBook = new Book;
	int count[4] = { 0 };
	int index = 0;
		for (int i = 0; i < input->tags.size(); i++) {
			if (typeid(*(input->tags[i])) == typeid(Title)) {
				editBook->set_Title(input->tags[i]->strarg());
				count[0]++;
			}
			if (typeid(*(input->tags[i])) == typeid(Author)) {
				editBook->set_Author(input->tags[i]->strarg());
				count[1]++;
			}
			if (typeid(*(input->tags[i])) == typeid(Publisher)) {
				editBook->set_Publisher(input->tags[i]->strarg());
				count[2]++;
			}
			if (typeid(*(input->tags[i])) == typeid(Date)) {
				editBook->set_Date(input->tags[i]->strarg());
				count[3]++;
			}
		}
		for (int j = 0; j < book.size(); j++) {
			if (book.at(j)->get_ID() == input->tags[0]->strarg()) {
				editBook->set_ID(input->tags[0]->strarg());
				index = j;
				break;
			}
			else if (j == book.size() - 1 && book.at(j)->get_ID() != input->tags[0]->strarg()) {
				index = -1;
			}
		}
		if (index == -1) {
			throw IDNotFound(input->tags[0]);
			return;
		}
		for (int i = 0; i < 4; i++) {
			if (count[i] == 0) {
				switch (i) {
				case 0:editBook->set_Title(book.at(index)->get_Title()); break;
				case 1:editBook->set_Author(book.at(index)->get_Author()); break;
				case 2:editBook->set_Publisher(book.at(index)->get_Publisher()); break;
				case 3:editBook->set_Date(book.at(index)->get_Date()); break;
				}
			}
			else continue;
		}
		cout << "#\t| 도서명\t| 저자명 \t| 출판사명 \t| 출판년도 \t\n" << endl;
		book[index]->Print();
		cout <<"\n\n                       ↓ ↓ ↓                       \n\n";
		editBook->Print();
		cout <<"\n"<<endl;
		SubPrompt sp = SubPrompt("도서 정보를 수정하시겠습니까 ? (Y / N) >");
		if(sp.is_real()){
			book.at(index) = editBook;
			File tempfile = File("./BookShelf.txt");
			tempfile.export_book_list(book);
		}
}
void BookList::DelOP(TagBundle* input) {
	SubPrompt sp; 
	string index="";
	vector<Book*>::iterator iter = book.begin();
	for (int i = 0; i < input->tags.size(); i++) {
		if (typeid(*(input->tags[i])) == typeid(Del)) {
			for (int j = 0; j < book.size(); j++) {
					index = input->tags[i]->strarg();
				if (book.at(j)->get_ID() == index) {
					cout << "#\t| 도서명\t| 저자명 \t| 출판사명 \t| 출판년도 \t\n" << endl;
					book[j]->Print();
					cout << "\n"<<endl;
					sp= SubPrompt("도서 정보를 삭제하시겠습니까 ? (Y / N) >");
					if(sp.is_real()){
						iter += (j);
						book.erase(iter);
						File tempfile = File("./BookShelf.txt");
						tempfile.export_book_list(book);
						return;
					}
					else {
						return;
					}
				}
			}
		}
	}
	index = input->tags[0]->strarg();
	throw IDNotFound(input->tags[0]);
}

void BookList::PageOP(TagBundle* input) {
	int n = input->tags[0]->intarg();
	Print(n);
}

void BookList::ClearOP(TagBundle* input) {
	book.erase(book.begin(), book.end());
}

vector<Book> BookList::IdSearch(int id) {
	vector<Book> IdBook;
	Book temp;
	int ID = 0;

	if (book.size() == 0)
	{
		throw AccessEmptyFile();
	}
	else
	{
		for (int j = 0; j < book.size(); j++) {
			if (book.at(j)->get_ID() == to_string(id)) {
				ID = j;
			}
		}
		temp.set_Title(book[ID]->get_Title());
		temp.set_Author(book[ID]->get_Author());
		temp.set_Publisher(book[ID]->get_Publisher());
		temp.set_Date(book[ID]->get_Date());
		IdBook.push_back(temp);
		return IdBook;
	}
	
}

void BookList::Print(int n) {
	int page = book.size() / 10 + 1;
	cout << "\n=== 검색 결과(" << book.size() << "개 검색됨, " << n << "페이지/" << page << "페이지" << ") ===\n" << endl;
	cout << "#   |도서명 | 저자명 | 출판사명 | 출판년도\n" << endl;
	if (n == page) {
		for (unsigned int j = (n - 1) * 10; j < book.size(); j++) {
			book[j]->Print();
			cout << "\n"<<endl;
		}
	}
	else {
		for (unsigned int j = (n - 1) * 10; j < n * 10; j++){
			book[j]->Print();
			cout << "\n" << endl;
		}
		
	}
}
