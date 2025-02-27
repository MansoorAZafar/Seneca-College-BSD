#ifndef SDDS_CONTACT_H_
#define SDDS_CONTACT_H_
#include <iostream>
#include <fstream>
#include "Person.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 31, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds {
	class Contact : public Person {
		char* address = nullptr; // 1. address 
		//2. city
		char* city = nullptr;
		//3. province
		char province[3]{};
		//4. postal code
		char postalCode[7]{};
	public:
		Contact();
		~Contact();
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		void clear(); // set to invalid state
		operator bool()const;
		void operator~();
		Contact(const Contact& rhs);
		Contact& operator=(const Contact& rhs);
	};
	std::ostream& operator<<(std::ostream& ostr, const Contact& rhs);
}

#endif