#ifndef SDDS_BUS_H
#define SDDS_BUS_H
#include <iostream>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 20, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	const double bus_price = 125.34;

	class Bus {
	private:
		int noOfSeats = -1, noOfPassengers = -1;
		bool inService = false;
		void drawBus(int seats, int noOfPassengers, ostream& ostr) const;

	public:
		Bus(int seats = 20, int passengers = 0);
		ostream& display(ostream& ostr = cout) const;
		istream& read(istream& istr = cin);
		//Type Conversion Operator's
		explicit operator bool() const;
		operator int() const;
		explicit operator double() const;
		//Unary Operator's
		bool operator--(); //prefix
		bool operator++(); //prefix
		bool operator--(int); //postfix
		bool operator++(int); //postfix
		//Binary Operator's
		Bus& operator=(int value);
		Bus& operator+=(int value);
		Bus& operator+=(Bus& right);
		bool operator==(Bus& right);
	};
	//Helper Operator Functions
	int operator+=(int left, Bus& right);
	ostream& operator<<(ostream& ostr, const Bus& right);
	istream& operator>>(istream& istr, Bus& right);

}

#endif