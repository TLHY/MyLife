#include "FileIO.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

//�ش� ���Ͽ� ���� �͵��� �ùٸ��� �������� �˻簡 �ʿ���

vector<Book*> File::import_book_list()
{
	cout << "���� ������ �ҷ����� ��..." << endl;
	/*
	this->address ��ο� ����� ���Ϸ� ���� �����͸� �о���δ�
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

			//���� �о���̴� ������ ���� 500 ������ �Ѿ� ���ٸ�
			if (line > 500) {
				throw OverLine(line);
			}

			int book_data_index = 0;
			readFile.getline(book, 500);

			//�ùٸ� ������ �Է����� �˻�
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

			//�ߺ��Ǵ� ID�� �ִ��� �˻�
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
				cout << e.what() << "\b(" << e.line() << "�� ��)\n";
				continue;
			}


			//���� ������ �±׺��� ����
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
			//���� �� ����� ���� �˻�
			try { sample->Validate(); }
			catch (const InvalidArgument & e) {
				throw InvalidLine(line);
			}

			//catch (const exception &) {
			//	throw InvalidLine(line);
			//}
			//���Ϳ� ���� ���� Ǫ��
			tempbl.push_back(sample);
			bi++;
		}

		cout << "���� ������ �ҷ����� ����" << endl;

		readFile.close();
		return tempbl;

	}
	else {
		//������ ���� ��� �� ���ϰ� �� ���͸� ������ �� ���͸� ��ȯ
		cout << "���� ������ �ҷ����� ���� : ������ �������� �ʽ��ϴ�" << endl;
		cout << "�� ������ �����մϴ�" << endl;
		ofstream writeFile;
		writeFile.open(this->address);
		vector<Book*>tempbl;
		return tempbl;
	}
}


void File::export_book_list(vector<Book*>bl) {
	cout << "���� ������ �������� ��..." << endl;
	ofstream writeFile;
	writeFile.open(this->address);

	/*
	�Ű� ������ ����� Book���� �±׺��� ���Ͼ��� ������ ���� ���๮�ڸ� ����
	����� �Ѿ���� �����ʹ� ���� �˻���� ��ģ �ùٸ� �����Ͷ� ����
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

		cout << "���� ������ �������� ����" << endl;

	}
	else
	{
		cerr << "���� ������ �������� ���� : ������ �������� �ʽ��ϴ�" << endl;
		exit(-1);
	}

}

void File::export_book_unit(vector<Book*>bl) {
	/*
	�� ���� ���� ���� ���Ͽ� �����͸� ���� ����ų� �߰��� ��
	*/
	cout << "���� ���� �������� ��..." << endl;
	ofstream  writeFile;
	writeFile.open(this->address, ios::app);
	char book[500];
	ifstream readFile(this->address);
	readFile.getline(book, 500);

	if (readFile.is_open()) {
		//������ ���� ���·� ������ ���Ŀ� �߰� �޼ҵ�
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
			cout << "���� ���� �������� ����" << endl;
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
			cout << "���� ���� �������� ����" << endl;
		}
	}
	else {
		cerr << "���� ���� �������� ���� : ������ �������� �ʽ��ϴ�" << endl;
		exit(-1);
	}
}

bool File::is_Right_Data(string s) {
	/*
	����ǥ����
	*/
	regex data_check("^([0-9]*|[0-9]+)\t([ -~]+\t)+([0-9]+)\n?$");

	if (regex_match(s, data_check)) {
		return true;
	}
	else {
		return false;
	}
}