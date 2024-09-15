#include <iostream>
#include <fstream>
#include "Perishable.h"
using namespace std;
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds {



	char Perishable::itemType() const {
		return 'P';
	}

	ostream& Perishable::write(ostream& ostr) const {
		if (*this) {

			Item::write(ostr);
			if (this->type == POS_LIST) {
				ostr << "  ";
				this->date.display(ostr);
				ostr << " " << "|"; //<< endl;
			}
			else {
				ostr << "Expiry date: ";
				this->date.display(ostr);
				ostr << endl << "=============^" << endl;
			}
		}
		return ostr;
	}

	istream& Perishable::read(istream& istr) {
		Item::read(istr);
		this->date.dateOnly(true);
		cout << "Expiry date (YYYY/MM/DD)" << endl << "> ";
		istr >> this->date;
		return istr;
	}

	ofstream& Perishable::save(ofstream& ofstr) const {
		Item::save(ofstr);
		if (*this) {
			ofstr << ",";
			this->date.display(ofstr);
		}
		return ofstr;
	}

	ifstream& Perishable::load(ifstream& ifstr) {
		Item::load(ifstr);
		//Item::write(cout);
		if (!(ifstr.fail()) && *this) {
			Date tmp;
			tmp.dateOnly(true);
			char comma;
			ifstr >> comma >> tmp;
			//cout << comma << tmp << endl;
			if (tmp.operator bool()) {
				this->date = tmp;
			}
		}
		return ifstr;
	}


}