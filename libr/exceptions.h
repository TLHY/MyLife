#pragma once
#include "tag_parents.h"

/* ���α׷� ����
	���α׷��� �����ؾ� �� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class ProgramTerminated: public std::exception{};

/* ���� ���� �ĺ� ��ȣ �浹
	���Ͽ��� �ĺ� ��ȣ �浹�� �߰ߵǸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class ReduplicatedID : public std::exception {
private:
	const int _line;
public:
	ReduplicatedID(const int line) : std::exception(), _line(line) {};
	const char* what() const { return "[!] �ĺ� ��ȣ �浹�� �߰ߵǾ����ϴ�. ������ ������ ���� �������ּ���."; };
	const int line() const { return _line; };
};

/* ���� ���� ��ȿ���� ���� ��
	���Ͽ��� �ؼ��� �� ���� ���� �߰ߵǸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class InvalidLine : public std::exception {
private:
	const int _line;
public:
	InvalidLine(const int line) : std::exception(), _line(line) {};
	const char* what() const { return "[����] ���� ������ �ؼ��� �� ���� ���� �߰ߵǾ����ϴ�. ������ ������ ���� �������ּ���."; }
	const int line() const { return _line; };
};

/* ����� �� ���� �±�
	���ǵ��� ���� �±׸� �Է��ϸ� �� ���ܸ� �߻���ŵ�ϴ�.
	���� ���, :abcdef:�� ���� �±״� ���������δ� �ùٸ����� ���ǰ� �������� �����Ƿ� ����� �� ���� �±��Դϴ�.
*/
class InvalidTag : public std::exception {
private:
	const char* _name;
public:
	InvalidTag(const char* name) : std::exception(), _name(name) {};
	const char* what() const { return "[!] ����� �� ���� �±��Դϴ�."; };
	const char* name() const { return _name; };
};

/* ���� ��� �±� ���
	�� �Է¿� ���� ���� ��� �±װ� ���Ǿ��� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class MultipleOperationTags : public std::exception {
public:
	const char* what() const { return "[!] ���ÿ� ���� ��� �±׸� ����� �� �����ϴ�."; };
};

/* �ǹ� ���� ���� �±� ���
	���� �±װ� �ʿ� ���� ��� �±׿� ���� �±װ� ���� �ԷµǾ��� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class MeaninglessBookTag : public std::exception {
public:
	const char* what() const { return "[!] :add:, :edit: �±� �̿��� ��� �±׿� ���� �±׸� ���� �Է��� �� �����ϴ�."; };
};

/* �ϳ� �̻��� ���� �±� �ʿ�
   edit �±װ� ���� �� id �±׸� ������ �ϳ� �̻��� ���� �±װ� �ߺ� ���� ���� �Էµ��� ������ �� ���ܸ� �߻���ŵ�ϴ�.
*/
class NeedOneOrMoreBookTag : public std::exception {
public:
	const char* what() const { return "[!] �ĺ� ��ȣ �±׸� ������ �ϳ� �̻��� ���� �±װ� �ߺ����� �ʰ� �Է¿� ���ԵǾ�� �մϴ�."; };
};

/* ��� ���� �±� �ʿ�
   add �±װ� ���� �� id �±׸� ������ ��� ������ ���� �±װ� �ߺ� ���� ���� �Էµ��� ������ �� ���ܸ� �߻���ŵ�ϴ�.
*/
class NeedEveryBookTag : public std::exception {
public:
	const char* what() const { return "[!] �ĺ� ��ȣ �±׸� ������ ��� ���� �±װ� �ߺ����� �ʰ� �Է¿� ���ԵǾ�� �մϴ�."; };
};

/* �߸��� �Է�
	�� ������Ʈ���� ����ڰ� �Է��� ���ڿ��� ���� ��Ģ�� �����ϸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class InvalidInput : public std::exception {
private:
	const char* _input;
public:
	InvalidInput(const char* input) : std::exception(), _input(input) {};
	const char* what() const { return "[!] �Է��� �ùٸ��� �ʽ��ϴ�. �� ������Ʈ�� ���� ��Ģ�� Ȯ�����ּ���."; };
};

/*���� ��� ����
	��������Ʈ���� clear�� page�� ����� �� �����˻������ �������� ������ �� ���ܸ� �߻���ŵ�ϴ�.
*/
class NotResult : public std::exception {
public:
	const char* what() const { return "[!] ���� �˻� ����� �����ϴ�."; };
};

// TODO: add, edit �±� ���� �ߺ��� ���� �±� ��뵵 ���ܷ� ó���ؾ� ��

/* �±� ������ �����ϴ� ����
	�±� ������ �����ؾ� �ϴ� ��� ������ ���� �߻� Ŭ�����Դϴ�.
	�±� ������ �ʿ��� ���� Ŭ������ �� Ŭ������ ��ӹ޾Ƽ� �����մϴ�.
	�����ڷ� ���ܰ� �߻��� �±׸� �����ϰ� ���� �Լ��� �±׿� ������ �� �ֽ��ϴ�.
*/
class TagException : public std::exception {
private:
	const Tag* _tag;
public:
	TagException(const Tag* tag) : std::exception(), _tag(tag) {};
	const Tag* tag()  const{ return _tag; }
};

/* �ùٸ��� ���� ����
	�±װ� ��Ģ �˻縦 �� �� ���ڰ� ���� ������ �����ϸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class InvalidArgument : public TagException
{
public:
	InvalidArgument(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�."; }
};

/* ��ȸ�� �� ���� �ĺ� ��ȣ
	id �±��� ���ڰ� �������� �ʴ� id�� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class IDNotFound : public TagException {
public:
	IDNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] ��ȸ�� �� ���� �ĺ� ��ȣ�Դϴ�."; }
};

/* ��ȸ�� �� ���� ������
	page �±��� ���ڰ� �˻� ��� ���� �������� �ʴ� �������� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class PageNotFound : public TagException {
public:
	PageNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] ��ȸ�� �� ���� �������Դϴ�."; };
};

/* ���� ���� �� ����
*/
class OverLine : public std::exception {
private:
	const int _line;
public:
	OverLine(const int line) : std::exception(), _line(line) {};
	const char* what() const { return "[����] ������ ���� ������ 500���� �Ѿ�ϴ�."; }
	const int line() const { return _line; };

};
/*���Ͽ� 500���� �ʰ��ϴ� ������ ���� �� ���� ���� ��*/
class OverLineAdd : public std::exception {
private:
	const int _size;
public:
	OverLineAdd(const int size) : std::exception(), _size(size) {};
	const char* what() const { return "[!] ���Ͽ� ����� ���� ������ ������ 500�� �Դϴ�."; }
	const int size() const { return _size; };
};

class AccessEmptyFile : public std::exception {
public:
	AccessEmptyFile() :std::exception() {};
	const char* what() const { return "[!] �� ���Ͽ� ���� ���� Ȥ�� ���� ����� �����Ϸ� �մϴ�."; };
};