#include <iostream>
#include "PosIO.h"
using namespace std;
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	std::ostream& operator<<(std::ostream& ostr, const PosIO& rhs) {
		rhs.write(ostr);
		return ostr;
	}
	std::ofstream& operator<<(std::ofstream& ofstr, const PosIO& rhs) {
		rhs.save(ofstr);
		return ofstr;
	}

	std::istream& operator>>(std::istream& istr, PosIO& rhs) {
		rhs.read(istr);
		return istr;
	}
	std::ifstream& operator>>(std::ifstream& ifstr, PosIO& rhs) {
		rhs.load(ifstr);
		return ifstr;
	}

	PosIO::~PosIO() {}
}
