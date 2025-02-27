#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "GPAlist.h"
#include "File.h"
#include "UI.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 


namespace sdds {

	bool gpaQuery(const char* filename) {
		if (openFile(filename)) {
			menu();
			closeFile(filename);
			return true;

		}
		else {
			return false;
		}
	}

}