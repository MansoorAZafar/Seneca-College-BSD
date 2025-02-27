#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Dog.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	Dog::Dog(const char* name, int age, int m_numWalks) : Pet(name, age) {
		this->m_numWalks = m_numWalks;
	}
	void Dog::feed() {
		Pet::feed();
		if (this->isAlive()) {
			this->addCharge(this->DOG_FEED);
		}
	}
	void Dog::reSpawn() {
		Pet::reSpawn();
		this->addCharge(this->DOG_RESPAWN);
		this->m_numWalks = 0;
	}
	void Dog::operator++(int num) {
		if (this->isAlive()) {
			double healthDelta = 0.0;
			healthDelta += 0.15 * (getHugs() - 1);
			healthDelta += 0.10 * (getFeeds() - 2);
			healthDelta += 0.10 * (getGrooms() - 1);
			healthDelta += 0.20 * (this->m_numWalks - 2);
			this->applyHealthDelta(healthDelta);
			Pet::operator++(num);
			this->m_numWalks = 0;
		}		
	}
	Dog& Dog::operator=(const Dog& rhs) {
		if(this != &rhs){
			Pet::operator=(rhs);
			this->addCharge(this->DOG_FEE * 2); //times 2 plus fee
			//rhs.m_numWalks = 0;
		}
		return *this;
	}

	void Dog::walk() {
		if (this->isAlive()) {
			this->m_numWalks++;
		}
	}

	std::ostream& operator<<(std::ostream& os, Dog& rhs) {
		os << "** Generic Dog **\n";
		os << "   Walks: " << rhs.m_numWalks << endl;
		rhs.outputData(os);
		
		return os;
	}
}