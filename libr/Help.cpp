#include "Help.h"
#include "MainPrompt.h"
#include "exceptions.h"

Tag* Help::copy() const {
	return new Help(*this);
}
void Help::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Help::Print() const {
	cout << ":help:" << endl;
}
void Help::Operate(MainPrompt& main) {
	cout << "���� �±� ����/��Ģ" << endl;
	cout << "1):title: �������� �ǹ��ϸ�, ���ڰ� �ݵ�� �־���մϴ�. �˻����� �±׾��� �Է��ϴ� ��� :title:�� �±׷� �ٽ��ϴ�." << endl;
	cout << "2):author: ���ڸ��� �ǹ��ϸ�, ���ڰ� �ݵ�� �־���մϴ�." << endl;
	cout << "3):publisher: ���ǻ���� �ǹ��ϸ�, ���ڰ� �ݵ�� �־���մϴ�." << endl;
	cout << "4):date: ���ǳ⵵�� �ǹ��ϸ�, ���ڰ� �ݵ�� �־���մϴ�." << endl;
	cout << "5):id: �� ������ �ĺ� ��ȣ�� �ǹ��ϸ�, ���ڰ� �ݵ�� �������̿��� �մϴ�." << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "��� �±� ��Ģ" << endl;
	cout << "1):add: �Է¹��� ���� ������ ������ ���Ͽ� �߰��մϴ�.���� �Է¿� �ĺ� ��ȣ �±׸� ������ ��� ���� �±װ� ���ԵǾ�� �մϴ�. ���� �±׵��� ���ڸ� �̿��Ͽ� �߰��� ������ ������ �����մϴ�.";
	cout << ":add:�� ����) :add: :title: title :author: author :publisher: publisher :date: 2020" << endl;
	cout << "2):edit: �Է¹��� �ĺ� ��ȣ�� ���� ������ �����մϴ�. ���� �Է¿� �ش� �ĺ� ��ȣ�� ������ ���� ������ �����ؾ� �մϴ�. ��, ���� �Է¿� �ĺ� ��ȣ �±׸� ������ �ϳ� �̻��� ���� ���� �±װ� ���ԵǾ�� �մϴ�." << endl;
	cout << ":edit:�� ����) :edit: 10 :title: fun :author: cool" << endl;
	cout << "3):del: �Է¹��� �ĺ� ��ȣ�� ���� ������ ������ ���Ͽ��� �����մϴ�. �ش� �ĺ� ��ȣ�� ������ ���� ������ �־�� �մϴ�." << endl;
	cout << ":del:�� ����) :del: 10" << endl;
	cout << "4):page: ���� �˻� ����� Ư�� �������� ����մϴ�. �˻� ����� ������ �������� ������ ���ԵǴ� ���� ������ �Է��ؾ��մϴ�." << endl;
	cout << ":page:�� ����) :page: 4" << endl;
	cout << "5):help: ���α׷��� ���� ������ ����մϴ�." << endl;
	cout << ":help:�� ����) :help:" << endl;
	cout << "6):clear: ���� �˻� ����� �ʱ�ȭ�մϴ�." << endl;
	cout << ":clear:�� ����) :clear:" << endl;
	cout << "7):exit: ���α׷��� �����մϴ�." << endl;
	cout << ":exit:�� ����) :exit:" << endl;
}
