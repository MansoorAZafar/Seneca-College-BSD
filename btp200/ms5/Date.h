#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Error.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class Date
	{
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
	protected:
		bool flag = false;
	public:
		Error err = {};
		int valid() const;
		Date();
		Date(int year, int month, int day, int hour = 0, int minute = 0);
		//(==, != , < , > , <= , >=)
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		Date& dateOnly(bool flag);
		/*Date& operator=(Date& rhs);*/
		operator bool() const;
		const Error& error() const;
		std::ostream& display(std::ostream& ostr) const; // added myself
		Date& set(const int& year, const int& month, const int& day, const int& hour = 0, const int& minute = 0);
	};
	std::ostream& operator<<(std::ostream& ostr, Date& rhs);
	std::istream& operator>>(std::istream& istr, Date& rhs);
}
#endif