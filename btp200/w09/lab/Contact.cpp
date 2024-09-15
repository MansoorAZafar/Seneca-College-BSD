#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Contact.h"
#include "Tools.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 31, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds{
	//default constructor
	Contact::Contact() : Person() { this->clear(); }

	Contact::~Contact(){ ~*this; }

	std::istream& Contact::read(std::istream& istr){
		Person::read(istr);
		this->address = dynRead(istr, ',');
		this->city = dynRead(istr, ',');
		istr.getline(this->province, 3, ',');
		istr.getline(this->postalCode, 7);
		if (istr.fail()) {
			~*this;
		}
		return istr;
		
	}

	std::ostream& Contact::write(std::ostream& ostr) const{
		Person::write(ostr);
		if (*this) {
			ostr << "\n" << this->address << endl << this->city << " " << this->province << endl;
			for (auto i = 0; i < strLen(this->postalCode); i++) {
				if (i == 2) {
					ostr << postalCode[i] << " ";
				}
				else {
					ostr << postalCode[i];
				}
			}
			ostr << endl;
		}
		return ostr;
	}
	
	void Contact::clear(){
		this->address = nullptr;
		this->city = nullptr;
		this->province[0] = '\0';
		this->postalCode[0] = '\0';
	}
	
	Contact::operator bool() const{
		if (Person::operator bool()) {
			if (this->address != nullptr && this->address[0] != '\0') {
				if (this->city != nullptr && this->city[0] != '\0') {
					if (this->province[0] != '\0') {
						if (this->postalCode[0] != '\0') {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	
	void Contact::operator~(){
		Person::operator~();
		delete[] this->address;
		delete[] this->city;
		this->address = nullptr;
		this->city = nullptr;
	}

	Contact::Contact(const Contact& rhs)
	{
		//this constructor calls this->operator=(const Contact&)
		//I call Person::operator=(rhs) in this->operator= 
		//So don't need to use : Person(rhs) for this constructor
		*this = rhs;
	}

	Contact& Contact::operator=(const Contact& rhs)
	{
		if (this != &rhs) {
			//Check for self-assessment
			Person::operator=(rhs); // set the person qualities the same
			delAlloCopy(this->address, rhs.address); 
			delAlloCopy(this->city, rhs.city);
			strCpy(this->province, rhs.province);
			strCpy(this->postalCode, rhs.postalCode);
		}
		return *this;
	}

	std::istream& operator>>(std::istream& istr, Contact& rhs){
		rhs.read(istr);
		return istr;
	}
	
	std::ostream& operator<<(std::ostream& ostr, const Contact& rhs) {
		rhs.write(ostr);
		return ostr;
	}
}