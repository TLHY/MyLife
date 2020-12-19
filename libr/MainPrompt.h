#pragma once
#include "TagBundle.h"
#include "FileIO.h"
#include "BookList.h"

class MainPrompt
{
private:
	BookList _entire_books;
	BookList _searched_books;
	std::string _raw_input;
	TagBundle _input_bundle;
	File _file;

	/* ���ڿ��� �ش��ϴ� �±׸� �����Ҵ��Ͽ� ��ȯ�ϴ� �Լ�
		�ùٸ��� ���� ���ڿ��� ���ڷ� �����ϸ� ���ܸ� �߻���ŵ�ϴ�.
	*/
	Tag* GetTag(const std::string str) const;

public:
	// ������
	MainPrompt();

	// ��� ���� ���� �Լ�
	BookList& entire_books();
	BookList& searched_books();
	std::string& raw_input();
	TagBundle& input_bundle();

	/* �� ������Ʈ ���� �Լ�
		����ڷκ��� ���ڿ��� �Է¹޾� �˻�, �ؼ�, ó���� �ϴ� �Լ��Դϴ�.
	*/
	void Prompt();
};


