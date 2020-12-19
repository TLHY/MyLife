#include <iostream>
#include <typeinfo>
#include "MainPrompt.h"
int main() {
	MainPrompt* mp;
	try {
		mp = new MainPrompt;
	}
	catch (const InvalidLine& e) {
		cout << e.what() << "\b(" << e.line() << "�� ��)\n";
		system("PAUSE");
		return 0;
	}
	catch (OverLine& e) {
		cout << e.what() << endl;
		system("PAUSE");
		return 0;
	}
	cout << "Booking ���α׷� ����" << endl;
	while (true) {
		try { mp->Prompt(); }
		catch (ProgramTerminated) {
			cout << "�����մϴ�" << endl;
			break;
		}
		catch (InvalidLine& e) {
			cout << e.what() << " " << e.line() << endl;
			break;
		}
		catch (InvalidTag& e) {
			cout << e.what() << " " << e.name() << endl;
			continue;
		}
		catch (InvalidArgument& e) {
			cout << e.what() << " ";
			e.tag()->Print();
			cout << endl;
		}
		catch (TagException & e) {
			cout << e.what() << " " << e.tag() << endl;
			continue;
		}
		catch (std::exception& e) {
			cout << e.what() <<endl;
			continue;
		}
	}
	delete mp;
	system("PAUSE");
	return 0;
}