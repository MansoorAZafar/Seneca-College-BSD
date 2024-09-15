#define CRTS_NO_SECURE_WARNINGS
#include "Bus.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 20, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	void Bus::drawBus(int seats, int noOfPassengers, ostream& ostr) const {
		int i, p;
		ostr.fill('_');
		ostr.width((seats / 2) * 3 + 4);
		ostr << "_";
		ostr << endl << "| ";
		for (i = 0, p = -1; i < (seats / 2); i++, ostr << "[" << ((p += 2) < noOfPassengers ? '2' : ((p == noOfPassengers) ? '1' : ' ')) << "]");
		ostr << "|_\\_" << endl;
		ostr << "| ";
		ostr.fill(' ');
		ostr.width(((seats / 2) * 3 - 14) / 2);
		ostr << " " << "Seneca College";
		ostr.width(((seats / 2) * 3 - 14) / 2 + (seats % 4 != 0));
		ostr << " " << "    )" << endl;
		ostr << "`---OO";
		ostr.fill('-');
		ostr.width((seats / 2) * 3 - 5);
		ostr << "-" << "O---'" << endl;
	}

	Bus::Bus(int seats, int passengers) {
		if (seats % 2 == 0 && (seats >= 10 && seats <= 40) && (passengers >= 0 && passengers <= seats)){
			this->noOfSeats = seats;
			this->noOfPassengers = passengers;
			this->inService = true;
		}
		else {
			this->noOfSeats = -1;
			this->noOfPassengers = -1;
			this->inService = false;
		}
	}

	ostream& Bus::display(ostream& ostr) const {
		if(*this){
			this->drawBus(this->noOfSeats, this->noOfPassengers, ostr);
			auto oldPrecision = ostr.precision(2);
			auto oldf = ostr.setf(ios::fixed);
			cout << "Total Fare Price: " << this->operator double() << endl;
			ostr.precision(oldPrecision);
			ostr.setf(oldf);
		}
		else {
			cout << "Out of service!\n";
		}
		return ostr;
	}

	istream& Bus::read(istream& istr){
		char seperator;
		cin >> this->noOfSeats >> seperator >> this->noOfPassengers;
		if (*this && this->noOfPassengers <= this->noOfSeats && (this->noOfSeats <= 40 && this->noOfSeats >= 10))
			this->inService = true;
		else {
			this->inService = false;
		}
		return istr;
	}

	//Type Conversion Operator's
	Bus::operator bool() const {
		return (this->noOfSeats >= 0 && this->inService == true);
	}

	Bus::operator int() const {
		if (*this)
			return this->noOfPassengers;
		return -1;
	}

	Bus::operator double() const {
		if (*this)
			return bus_price * this->noOfPassengers;
		return -1.0;
	}

	//Unary Operator's
	bool Bus::operator--() {
		if (*this && this->operator int() > 0){
			this->noOfPassengers--;
			return true;
		}
		return false;
	}

	bool Bus::operator++(){
		if (*this && this->noOfSeats > this->noOfPassengers) {
			this->noOfPassengers++;
			return true;
		}
		return false;
	}

	bool Bus::operator--(int){
		//"Works exactly like the prefix operator--"
		//When I tried to write this code the numbers wouldn't be correct
		// Bus tmp = *this;
		// this->operator--();
		// return tmp;
		//However, when I return the operator-- it works perfectly fine?
		return this->operator--(); //Why does it only work with this??
	}
	bool Bus::operator++(int) {
		return this->operator++(); // why does it only work with this??
	}
	//Binary Operator's
	Bus& Bus::operator=(int value) {
		this->noOfPassengers = value;
		if (this->noOfPassengers > this->noOfSeats)
			this->inService = false;
		return *this;
	}

	Bus& Bus::operator+=(int value) {
		if (*this)
			this->noOfPassengers += value;
		if (this->noOfSeats < this->noOfPassengers)
			this->inService = false;
		return *this;
	}

	Bus& Bus::operator+=(Bus& right) {
		if (this->operator bool() && right.operator bool()) {
			//Check if both buses are in service
			auto diff = this->noOfSeats - this->noOfPassengers;
			if (right.operator int() > diff) {
				this->noOfPassengers += diff;
				right = (right.operator int() - diff);
			}
			else {
				this->noOfPassengers += right.operator int();
				right.noOfPassengers = 0;
			}
		}
		//"left" bus is *this 
		return *this;
	}

	bool Bus::operator==(Bus& right) {
		if ((*this && right.operator bool()) && (this->noOfPassengers == right.noOfPassengers))
			return true;
		return false;
	}

	//Helper Operator's
	int operator+=(int left, Bus& right) {
		if (right.operator bool())
			return left + right.operator int();
		return left;
	}
	
	ostream& operator<<(ostream& ostr, const Bus& right) {
		right.display();
		return ostr;
	}

	istream& operator>>(istream& istr, Bus& right) {
		right.read();
		return istr;
	}
	
}