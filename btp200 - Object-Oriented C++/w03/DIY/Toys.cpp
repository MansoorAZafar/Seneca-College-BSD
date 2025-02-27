#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Toys.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;

namespace sdds {

	void Toys::addToys(const char* tname, int sku, double price, int age) {

		if ((tname != nullptr) && (sku > 10000000 && sku < 99999999)) {
			strcpy(this->m_tname, tname);
			this->m_sku = sku;
			this->m_price = price;
			this->m_age = age;
		}
		else {
			this->m_tname[0] = '\0';
			this->m_sku = 0;
			this->m_price = 0.0;
			this->m_age = 0;
		}
	}

	void Toys::isSale(bool sale) {
		this->m_onSale = sale;
	}

	void Toys::calSale() {
		if (this->m_onSale) {
			this->m_price = this->m_price - (this->m_price * 0.2);
		}
	}

	void Toys::display()const {

		
		if (this->m_tname[0] != '\0' || this->m_sku > 0) {
			//SKU HAS TO BE 8 DIGITS
			//IF SKU CAN BE ANY NUMBER UP TO 8
			// SET TNAME TO NULLPTR FROM SETTOYS IN THE ADDTOYS
			//TLDR
			// do this
			// for loop to check if any of the names in the loop have been nullptr
			// If yes: Set tname to nullptr
			// If no: Leave it
			// That would fix it and then sku can be any amount of digits upto 8
			cout.width(15);
			cout.fill(' ');
			cout << left << this->m_tname;
			cout.unsetf(ios::left);
			cout.width(10);
			cout << this-> m_sku;
			cout.width(6);
			cout << this->m_age;
			cout.width(12);
			cout << fixed << setprecision(2) << this->m_price;
			if(this->m_onSale == true){
				cout.width(10);
				cout << "On Sale" << " ";
			}
			else{
				cout.width(8);
				cout.fill(' ');
				cout << " ";
			}
			cout << endl;
		}
		else {
						cout << "Invalid Toy" << endl;
		}
	}



}