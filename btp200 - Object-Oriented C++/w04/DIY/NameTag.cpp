#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "NameTag.h"
#include <string>
#define MAX_SIZE 40
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 26, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	NameTag::NameTag() {
		this->digit = 0;
		this->name = nullptr;
	}

	NameTag::NameTag(const char* str) {
		if (str == nullptr) {
			this->digit = 0;
			this->name = nullptr;
		}
		else {
			this->name = new char[strlen(str) + 1];
			strcpy(this->name, str);
			this->digit = 0;
		}
	}

	NameTag::NameTag(const char* str, int val) {
		if (str == nullptr) {
			this->digit = 0;
			this->name = nullptr;
		}
		else {
			this->name = new char[strlen(str) + 1];
			strcpy(this->name, str);
			if (val > 9999 && val < 100000) {
				this->digit = val;
			}
			else {
				this->digit = -1;
			}
		}
	}

	NameTag::~NameTag() {
		this->digit = 0;
		//this->name[0] = '\0';
		delete[] this->name;
		this->name = nullptr;
	}

	void NameTag::print() const{
		if (name == nullptr || this->digit == -1) {
			cout << "EMPTY NAMETAG!" << endl;
		}
		else {
			//Starting format
			auto size = strlen(this->name);
			cout << "+";
			auto defaultval = cout.width(43);
			if (size < 40) { cout.width(23); }
			auto defaultfill = cout.fill('-');
			cout << "+" << endl;
			cout << "|";
			cout.width(43);
			if (size < 40) { cout.width(23); }
			cout.fill(' ');
			cout << "|" << endl;
			cout.width(defaultval);
			cout.fill(defaultfill);

			//All good ^

			//Printing out name
			auto diff = MAX_SIZE - size;

			cout << "| ";
			if (size > MAX_SIZE) {

				for (int i = 0; i < MAX_SIZE; i++) {
					cout << name[i];
				}
			}
			else {
				cout << name;
			}
			cout.width(diff + 2);
			if (size < 40) { diff = 23 - size - 1; cout.width(diff); }
			//Formula for diff is : max num of spaces - length of name -1 because of space before the name is printed
			cout.fill(' ');
			cout << " |" << endl;

			//Format
			cout << "|";
			cout.width(43);
			if (size < 40) { cout.width(23); }
			cout.fill(' ');
			cout << "|" << endl;

			//Printing out Extension
			cout << "| Extension: ";

			if (this->digit) {
				diff = MAX_SIZE - 5; // max amt of numbers a digit is
				cout << this->digit;
				cout.width(diff - 9);
				if (size < 40) { cout.width(6); }
				cout << "|" << endl;

			}
			else {
				diff = MAX_SIZE - 3; // size of N/A
				cout << "N/A";
				cout.width(diff - 9);
				if (size < 40) { cout.width(6); }
				cout << "|" << endl;
			}

			//Format
			cout << "|";
			cout.width(43);
			if (size < 40) { cout.width(23); }
			cout.fill(' ');
			cout << "|" << endl;

			//Ending format
			cout << "+";
			cout.width(43);
			if (size < 40) { cout.width(23); }
			cout.fill('-');
			cout << "+" << endl;
		}
	}

	NameTag& NameTag::read() {
		char tmp[100];
		cout << "Please enter the name: ";
		cin.getline(tmp, 100);
		delete[] this->name;
		this->name = new char[strlen(tmp) + 1];
		strcpy(this->name, tmp);
		//Hubert Blaine Wolfeschlegelsteinhausenbergerdorff

		cout << "Would you like to enter an extension? (Y)es/(N)o: ";
		char choice;
		cin >> choice;
		while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
			cout << "Only (Y) or (N) are acceptable, try agin: ";
			cin >> choice;
		}
		if (choice == 'Y' || choice == 'y') {
			bool flag = false;
			cout << "Please enter a 5 digit phone extension: ";
			while (!flag) {
				cin >> this->digit;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Bad integer value, try again: ";

				}
				else if ((this->digit <= 9999 || this->digit >= 100000)) {
					cout << "Invalid value [10000<=value<=99999]: ";

				}
				else {
					flag = true;
				}
			}
		}
		else {
			this->digit = 0;
		}
		cin.clear();
		cin.ignore();
		return *this;
	}

}