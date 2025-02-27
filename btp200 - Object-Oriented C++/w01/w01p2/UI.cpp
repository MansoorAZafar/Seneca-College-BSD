#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "File.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 

namespace sdds {



	void exitProgram(bool& refFlag) {
		char choice;
		cout << "Exit the program? (Y)es/(N)o: "; cin >> choice;
		switch (choice) {
		case 'y': refFlag = false; break;
		case 'n': break;
		default: break;
		}
	}

	void takeInput(char& op, double& val, bool& flag) {
		cin >> op;
		if (op == '!') {
			exitProgram(flag);
		}
		else {
			cin >> val;
		}
	}


	void menu() {
		double value; char op; bool flag = true;
		int counter = 0;
		cout << "Enter GPA query...\n? ";
		takeInput(op, value, flag);
		setValues(counter);

		while (flag) {
			if (op == '~') {
				findMatch(counter, value); cout << "? "; takeInput(op, value, flag);
			}
			else if (op == '>') {
				findGreater(counter, value); cout << "? "; takeInput(op, value, flag);
			}
			else if (op == '<') {
				findLess(counter, value); cout << "? "; takeInput(op, value, flag);
			}
			else {
				cout << "Syntax error: ? [Op][value]<ENTER>\nOp: [>,<,~,!]\nvalue: GPA value\n\n? "; takeInput(op, value, flag);
			}
		}

	}


}