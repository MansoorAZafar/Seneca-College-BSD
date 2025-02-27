#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Store.h"
#include "Toys.h"
#include <cstring>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
using namespace std;
namespace sdds {
	void Store::setStore(const char* sName, int no) {
		setEmpty();
		if (strlen(sName) > MAX_SNAME && strlen(sName) <= 0) {
			;	
		}
		else {
			strcpy(this->m_sName, sName);
			this->m_noOfToys = no;
		}
	}

	void Store::setToys(const char* tname, int sku, double price, int age) {
		this->m_toy[this->m_addToys].addToys(tname, sku, price, age);
		this->m_addToys++;
	}

	void Store::display()const {

		if (this->m_sName[0] != '\0') {
			//cout << "Madd is :" << this->m_addToys << "\n and mNoOf is : " << m_noOfToys;
			
				cout.width(60); cout.fill('*');
				cout << "" << endl;
				cout << this->m_sName << endl;
				//cout.width(60); cout.fill('*');
				cout.width(60); cout.fill('*');
				cout << "" << endl;

				cout << "list of the toys" << endl;

				cout.width(27); cout.fill(' ');
				cout << "";
				cout << "SKU";
				cout.width(7); cout.fill(' ');
				cout << "";
				cout << "Age";
				cout.width(6); cout.fill(' ');
				cout << "";
				cout << "Price";
				cout.width(6); cout.fill(' ');
				cout << "";
				cout << "Sale";
				//cout.width(10); cout.fill(' ');
				cout << endl;
				for (int i = 0; i < this->m_noOfToys; i++) {					
					cout << "Toy[" << i + 1 << "] :";
					this->m_toy[i].display();
						
				}
			
		}
		else {
			cout << "Invalid Store" << endl;
		}
		cout.width(0);
	}

	void Store::find(int sku) {
		for (int i = 0; i < this->m_noOfToys; i++) {
			if (this->m_toy[i].m_sku == sku) {
				this->m_toy[i].isSale(true);
				this->m_toy[i].calSale();
			}
		}
	}

	void Store::setEmpty() {
		this->m_addToys = 0;
		this->m_noOfToys = 0;
		this->m_sName[0] = '\0';
	}
}