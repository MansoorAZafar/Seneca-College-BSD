#include <iostream>
#include "GPAlist.h"
using namespace std;
using namespace sdds;


// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 


int main() {
	if (gpaQuery("std.csv")) {
		std::cout << "This should have failed!" << std::endl;
	}
	else {
		std::cout << "failed!, this is the correct exectution" << std::endl;
	}
	if (!gpaQuery("students.csv")) {
		std::cout << "This should have worked, fix the problem!" << std::endl;
	}
	std::cout << "Goodbye!" << std::endl;
	return 0;
}