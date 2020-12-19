#include <iostream>
#include <typeinfo>
#include "MainPrompt.h"
int main() {
	MainPrompt* mp;
	try {
		mp = new MainPrompt;
	}
	catch (const InvalidLine& e) {
		cout << e.what() << "\b(" << e.line() << "번 줄)\n";
		system("PAUSE");
		return 0;
	}
	catch (OverLine& e) {
		cout << e.what() << endl;
		system("PAUSE");
		return 0;
	}
	cout << "Booking 프로그램 시작" << endl;
	while (true) {
		try { mp->Prompt(); }
		catch (ProgramTerminated) {
			cout << "종료합니다" << endl;
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