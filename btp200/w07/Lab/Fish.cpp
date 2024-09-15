#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Fish.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	Fish::Fish(const char* name, int age) : Pet(name, age) {

	}
	void Fish::feed() {
		Pet::feed();
		if (Pet::isAlive()) {
			Pet::addCharge(this->FISH_FEED);

		}
	}
	void Fish::reSpawn() {
		Pet::reSpawn();
		Pet::addCharge(this->FISH_RESPAWN);
	}
	void Fish::operator++(int num) {
		if (Pet::isAlive()) {
			double healthDeleta = 0;
			healthDeleta += 0.20 * (getFeeds() - 1);
			Pet::applyHealthDelta(healthDeleta);
			Pet::operator++(0);
		}
	}
	Fish& Fish::operator=(const Fish& rhs) {
		Pet::operator=(rhs);
		Pet::addCharge(this->FISH_FEE * 2 + this->FISH_FEE); //times 2 plus fee
		return *this;
	}
	std::ostream& operator<<(std::ostream& os, Fish& rhs) {
		os << "** Generic Fish **\n";
		rhs.outputData(os);
		return os;
	}
}