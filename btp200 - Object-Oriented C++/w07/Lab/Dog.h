#ifndef SDDS_DOG_H
#define SDDS_DOG_H
#include <iostream>
#include "Pet.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	class Dog : public Pet {
		const double DOG_FEE = 4.00;
		const double DOG_FEED = 0.25;
		const double DOG_RESPAWN = 1.00;
	public:
		int m_numWalks = 0; // Per day
		Dog(const char* name, int age = 0, int m_numWalks = 0);
		void feed();
		void reSpawn();
		void operator++(int num);
		Dog& operator=(const Dog& rhs);
		void walk();
	};
	std::ostream& operator<<(std::ostream& os, Dog& rhs);
}


#endif