#define CRTS_NO_SECURE_WARNINGS
#include "EggCarton.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	EggCarton tmp = {};
	//Made to counteract the unused/unitialized memory warning if used in the scope of the post fix operators
	//If not made here, will get warning

	EggCarton::EggCarton(int size, int noOfEggs, bool jumboSize) {
		if (size % 6 == 0 && size <= 36 && (noOfEggs <= size && noOfEggs >= 0)) {
			this->size = size;
			this->operator=(noOfEggs);
			this->jumboSize = jumboSize;
		}
		else {
			this->setBroken();
		}
	}

	void EggCarton::setBroken() {
		this->size = -1;
		this->noOfEggs = 0;
	}

	ostream& EggCarton::displayCarton(int size, int noOfEggs, bool jumbo, ostream& ostr)const {
		int cartonWidth = size == 6 ? 3 : 6;
		for (int i = 0; i < size; i++) {
			ostr << ((i % cartonWidth) ? '|' : '[') << ((i < noOfEggs) ? (jumbo ? 'O' : 'o') : ' ');
			((i + 1) % cartonWidth == 0) && ostr << ']' << endl;
		}
		return ostr;
	}

	ostream& EggCarton::display(ostream& ostr) const {
		if (this->operator bool() && this->noOfEggs <= size) {
			displayCarton(this->size, this->noOfEggs, this->jumboSize, ostr);
		}
		else {
			ostr << "Broken Egg Carton!\n";
		}
		return ostr;
	}

	istream& EggCarton::read(istream& istr) {
		char ch, seperator; int size, numOfEggs;
		istr >> ch >> seperator >> size >> seperator >> numOfEggs;
		if (ch == 'j') {
			this->jumboSize = true;
			this->size = size;
			this->noOfEggs = numOfEggs;
		}
		else if (ch == 'r') {
			this->jumboSize = false;
			this->size = size;
			this->noOfEggs = numOfEggs;
		}
		else {
			this->setBroken();
		}
		if (this->operator bool() && this->noOfEggs <= this->size)
			return istr;
		this->setBroken();
		return istr;
	}

	EggCarton::operator bool() const {
		return size > 0 && size <= 36; // return true if NOT broken
	}

	EggCarton::operator int() const {
		if (this->operator bool())
			return this->noOfEggs;
		return -1;
	}

	EggCarton::operator double() const {
		if (this->jumboSize)
			return (JumboEggWieght * this->noOfEggs) / 1000.0f;
		return (RegularEggWieght * this->noOfEggs) / 1000.0f;
	}

	EggCarton& EggCarton::operator--() {
		if (operator bool())
			this->noOfEggs--;
		return *this;
	}

	EggCarton& EggCarton::operator++() {
		if (operator bool())
			this->noOfEggs++;
		if (this->noOfEggs > size)
			setBroken();
		return *this;
	}

	EggCarton& EggCarton::operator--(int) {
		tmp = *this;
		this->operator--();
		return tmp;
	}

	EggCarton& EggCarton::operator++(int) {
		tmp = *this;
		this->operator++();
		return tmp;

	}

	EggCarton& EggCarton::operator=(int value) {
		this->noOfEggs = value;
		if (this->noOfEggs > this->size)
			setBroken();
		return *this;
	}

	EggCarton& EggCarton::operator+=(int value) {
		if (this->operator bool())
			this->noOfEggs += value;
		if (this->noOfEggs > this->size)
			setBroken();
		return *this;
	}

	EggCarton& EggCarton::operator+=(EggCarton& right) {
		if (this->operator bool()) {
			//if not broken
			auto diff = this->size - this->noOfEggs; // how many eggs left that can fit inside the original size //Remaining Eggs Needed till full
			if (right.noOfEggs > diff) {
				this->operator+=(diff); //If there are too many eggs in right : just add the difference
				right.operator=(right.noOfEggs - diff);
			}
			else {
				this->operator+=(right.noOfEggs); //If there are too little amt of eggs in right : just add the amt of eggs in right : SINCE IT'LL STILL BE UNDER / EQUAL
				right.noOfEggs = 0;

			}
		}
		return *this;
	}

	bool EggCarton::operator==(const EggCarton& right) const {
		auto diff = this->operator double() - right.operator double();
		if (diff >= -0.001 && diff <= 0.001)
			return true;
		return false;
	}

	int operator+(int left, const EggCarton& right) {
		if (right)
			return left += right.operator int();
		else {
			return left;
		}
	}

	ostream& operator<<(ostream& ostr, const EggCarton& right) {
		right.display();
		return ostr;
	}

	istream& operator>>(istream& istr, EggCarton& right) {
		right.read();
		return istr;
	}
}