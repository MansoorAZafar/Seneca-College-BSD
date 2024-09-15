#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class PosIO {
	public:
		~PosIO();
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual std::ofstream& save(std::ofstream& ofstr) const = 0;
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
	};
	//Inseration + extraction operators
	std::ostream& operator<<(std::ostream& ostr, const PosIO& rhs);
	std::ofstream& operator<<(std::ofstream& ofstr, const PosIO& rhs);

	std::istream& operator>>(std::istream& istr, PosIO& rhs);
	std::ifstream& operator>>(std::ifstream& ifstr, PosIO& rhs);
}

#endif // !SDDS_POSAPP_H