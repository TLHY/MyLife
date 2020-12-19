#include "FileIO.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

//해당 파일에 쓰인 것들이 올바르게 쓰였는지 검사가 필요함

vector<Book*> File::import_book_list()
{
	cout << "도서 정보들 불러오기 중..." << endl;
	/*
	this->address 경로에 저장된 파일로 부터 데이터를 읽어들인다
	*/

	ifstream readFile;
	readFile.open(this->address);

	if (readFile.is_open())
	{
		vector<Book*>tempbl;
		int bi = 0;
		string samplebook[5];
		char book[500];
		int line = 0;
		while (!readFile.eof())
		{
			line++;

			//지금 읽어들이는 파일의 행이 500 라인을 넘어 간다면
			if (line > 500) {
				throw OverLine(line);
			}

			int book_data_index = 0;
			readFile.getline(book, 500);

			//올바른 데이터 입력인지 검사
			if (!this->is_Right_Data(book))
			{
				throw InvalidLine(line);
			}

			Book* sample = new Book();
			char* parsing = strtok(book, "\t");
			while (parsing != NULL) {
				samplebook[book_data_index] = parsing;
				book_data_index++;
				parsing = strtok(NULL, "\t");
			}

			//중복되는 ID가 있는지 검사
			int dup_flag = 0;
			try
			{
				for (int t = 0; t < tempbl.size(); t++)
				{

					if (tempbl.at(t)->get_ID() == samplebook[0])
					{
						throw ReduplicatedID(line);
					}

				}
			}
			catch (const ReduplicatedID& e) {
				cout << e.what() << "\b(" << e.line() << "번 줄)\n";
				continue;
			}


			//도서 정보를 태그별로 대입
			for (int k = 0; k < book_data_index; k++) {
				if (k == 0) {
					sample->set_ID(samplebook[0]);
				}
				else if (k == 1) {
					sample->set_Title(samplebook[1]);
				}
				else if (k == 2) {
					sample->set_Author(samplebook[2]);
				}
				else if (k == 3) {
					sample->set_Publisher(samplebook[3]);
				}
				else if (k == 4) {
					sample->set_Date(samplebook[4]);
				}
			}
			//샘플 각 요소의 문법 검사
			try { sample->Validate(); }
			catch (const InvalidArgument & e) {
				throw InvalidLine(line);
			}

			//catch (const exception &) {
			//	throw InvalidLine(line);
			//}
			//벡터에 도서 정보 푸시
			tempbl.push_back(sample);
			bi++;
		}

		cout << "도서 정보들 불러오기 성공" << endl;

		readFile.close();
		return tempbl;

	}
	else {
		//파일이 없는 경우 빈 파일과 빈 벡터를 생성한 후 벡터를 반환
		cout << "도서 정보들 불러오기 실패 : 파일이 존재하지 않습니다" << endl;
		cout << "빈 파일을 생성합니다" << endl;
		ofstream writeFile;
		writeFile.open(this->address);
		vector<Book*>tempbl;
		return tempbl;
	}
}


void File::export_book_list(vector<Book*>bl) {
	cout << "도서 정보들 내보내기 중..." << endl;
	ofstream writeFile;
	writeFile.open(this->address);

	/*
	매개 변수에 저장된 Book들을 태그별로 파일쓰기 마지막 행은 개행문자를 생략
	여기로 넘어오는 데이터는 문법 검사들을 거친 올바른 데이터라 믿음
	*/
	if (writeFile.is_open()) {

		for (int i = 0; i < bl.size(); i++) {
			if (i == bl.size() - 1)
			{
				writeFile << bl.at(i)->get_ID() << "\t";
				writeFile << bl.at(i)->get_Title() << "\t";
				writeFile << bl.at(i)->get_Author() << "\t";
				writeFile << bl.at(i)->get_Publisher() << "\t";
				writeFile << bl.at(i)->get_Date();
			}
			else {
				writeFile << bl.at(i)->get_ID() << "\t";
				writeFile << bl.at(i)->get_Title() << "\t";
				writeFile << bl.at(i)->get_Author() << "\t";
				writeFile << bl.at(i)->get_Publisher() << "\t";
				writeFile << bl.at(i)->get_Date() << endl;
			}

		}

		writeFile.close();

		cout << "도서 정보들 내보내기 성공" << endl;

	}
	else
	{
		cerr << "도서 정보들 내보내기 실패 : 파일이 존재하지 않습니다" << endl;
		exit(-1);
	}

}

void File::export_book_unit(vector<Book*>bl) {
	/*
	한 도서 정보 별로 파일에 데이터를 덮어 씌우거나 추가할 때
	*/
	cout << "도서 정보 내보내기 중..." << endl;
	ofstream  writeFile;
	writeFile.open(this->address, ios::app);
	char book[500];
	ifstream readFile(this->address);
	readFile.getline(book, 500);

	if (readFile.is_open()) {
		//파일이 없는 상태로 실행한 이후에 추가 메소드
		if (strlen(book) == 0)
		{
			int i = bl.size() - 1;
			writeFile << bl.at(i)->get_ID() << "\t";
			writeFile << bl.at(i)->get_Title() << "\t";
			writeFile << bl.at(i)->get_Author() << "\t";
			writeFile << bl.at(i)->get_Publisher() << "\t";
			writeFile << bl.at(i)->get_Date();

			writeFile.close();
			readFile.close();
			cout << "도서 정보 내보내기 성공" << endl;
		}
		else
		{
			int i = bl.size() - 1;
			writeFile << endl << bl.at(i)->get_ID() << "\t";
			writeFile << bl.at(i)->get_Title() << "\t";
			writeFile << bl.at(i)->get_Author() << "\t";
			writeFile << bl.at(i)->get_Publisher() << "\t";
			writeFile << bl.at(i)->get_Date();

			writeFile.close();
			readFile.close();
			cout << "도서 정보 내보내기 성공" << endl;
		}
	}
	else {
		cerr << "도서 정보 내보내기 실패 : 파일이 존재하지 않습니다" << endl;
		exit(-1);
	}
}

bool File::is_Right_Data(string s) {
	/*
	정규표현식
	*/
	regex data_check("^([0-9]*|[0-9]+)\t([ -~]+\t)+([0-9]+)\n?$");

	if (regex_match(s, data_check)) {
		return true;
	}
	else {
		return false;
	}
}