#ifndef SDDS_FISH_H
#define SDDS_FISH_H
#include <iostream>
#include "Pet.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	class Fish : public Pet {
		const double FISH_FEE = 2.00;
		const double FISH_FEED = 0.10;
		const double FISH_RESPAWN = 0.50;
	public:
		Fish(const char* name, int age = 0);
		void feed();
		void reSpawn();
		void operator++(int num);
		Fish& operator=(const Fish& rhs);
	};
	std::ostream& operator<<(std::ostream& os, Fish& rhs);
}


#endif