#include "Subprompt.h"
#include <iostream>
#include <ios>

bool SubPrompt::is_real() {
	while (true) {
		cout << this->message;
		string answer;
		getline(cin, answer);
		if (answer == "Y" || answer =="y")
		{
			return true;
		}
		else if (answer == "N" || answer=="n")
		{
			return false;
		}
		else
		{
			cout << "�ٽ� �Է��� �ּ���" << endl;
			continue;
		}
	}
}