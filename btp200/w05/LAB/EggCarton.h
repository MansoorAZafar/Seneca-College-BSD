#ifndef SDDS_EGGCARTON_H 
#define SDDS_EGGCARTON_H
#include <iostream>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 17, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	const int RegularEggWieght = 50;
	const int JumboEggWieght = 75;
	//These weights are in Grams. (1000 Grams is one Kilo)

	class EggCarton {
	private:
		int size = 0;
		int noOfEggs = 0;
		bool jumboSize = false;
		void setBroken();
		ostream& displayCarton(int size, int noOfEggs, bool jumbo, ostream& ostr)const;
	public:
		EggCarton(int size = 6, int noOfEggs = 0, bool jumboSize = false);
		ostream& display(ostream& ostr = cout) const;
		istream& read(istream& istr = cin);
		operator bool() const;
		operator int() const;
		operator double() const;
		EggCarton& operator--();
		EggCarton& operator++();
		EggCarton& operator--(int);
		EggCarton& operator++(int);
		EggCarton& operator=(int value);
		EggCarton& operator+=(int value);
		EggCarton& operator+=(EggCarton& right);
		bool operator==(const EggCarton& right) const;
	};

	int operator+(int left, const EggCarton& right);
	ostream& operator<<(ostream& ostr, const EggCarton& right);
	istream& operator>>(istream& istr, EggCarton& right);

}

#endif