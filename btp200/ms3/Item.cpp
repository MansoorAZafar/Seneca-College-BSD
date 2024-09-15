#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "Utils.h"
#include "Item.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;

namespace sdds {

	Item& Item::displayType(int x) {
		this->type = x;
		return *this;
	}

	double Item::cost() const {
		if (this->taxed) {
			return this->price * 1.13;
		}
		return this->price;
	}

	int Item::quantity() const {
		return this->qty;
	}

	Item& Item::clear() {
		err.clear();
		return *this;
	}
	
	std::ostream& Item::write(std::ostream& ostr) const {
		if (*this) {
			if (this->type == POS_LIST) {
				if (strLen(this->name) > 20) {
					ostr << left << setw(7) << this->SKU << "|";

					for (auto i = 0; i < 20; i++) {
						ostr << this->name[i];
					}

					ostr << "|";

					ostr << setw(7) << right << this->price <<
						"| " << ((this->taxed) ? "X" : " ") << " |  " << this->qty << "|" << setw(9) << fixed << setprecision(2) << (this->cost() * this->qty) << "|";
				}
				else {
					ostr << left << setw(7) << this->SKU << "|" << left << setw(20) << this->name << "|" << setw(7) << right << this->price <<
						"| " << ((this->taxed) ? "X" : " ") << " |  " << this->qty << "|" << setw(9) << fixed << setprecision(2) << (this->cost() * this->qty) << "|";
				}
			}
			else {
				ostr << "=============v" << endl <<
					"Name:        " << this->name << endl <<
					"Sku:         " << this->SKU << endl <<
					"Price:       " << this->price << endl;
				if (this-> taxed) {
				ostr << "Price + tax: " << this->cost() << endl;
				}
				else {
				ostr << "Price + tax: N/A" << endl;
				}
				ostr << "Stock Qty:   " << this->qty;
				ostr << endl;
			}
		}
		else {
			ostr << this->err;
		}

		return ostr;
	}

	std::istream& Item::read(std::istream& istr) {
		//---------SKU ----------------//
		cout << "Sku" << endl << "> ";
		char* tmp;
		tmp = dynRead(istr, '\n');
		while (istr.fail() || strLen(tmp) > MAX_SKU_LEN) {
			istr.clear();
			this->err = ERROR_POS_SKU;
			cout << this->err << endl << "> ";
			delete[] tmp;
			tmp = dynRead(istr, '\n');
		}
		strCpy(this->SKU, tmp);

		//-------NAME-----------------//
		cout << "Name" << endl << "> ";
		this->name = dynRead(istr, '\n');
		if (strLen(this->name) > MAX_NAME_LEN) {
			this->err = ERROR_POS_NAME;
			cout << this->err << endl << "> ";
			delete[] this->name;
			this->name = dynRead(istr, '\n');
		}

		//---------PRICE--------------//
		cout << "Price" << endl << "> ";
		istr >> this->price;
		while (this->price < 0 || istr.fail()) {
			this->err = ERROR_POS_PRICE;
			if (istr.fail()) {
				istr.clear();
				istr.ignore(123, '\n');
				cout << this->err << endl;
				cout << "> ";
				istr >> this->price;
			}
			else {
				cout << this->err << endl;
				cout << "> ";
				istr >> this->price;
			}
		}

		//----------TAX------------------//
		cout << "Taxed?" << endl << "(Y)es/(N)o: ";
		char choice;
		istr >> choice;
		while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
			istr.clear();
			istr.ignore(100, '\n');
			this->err = ERROR_POS_TAX;
			cout << "Only 'y' and 'n' are acceptable: ";
			istr >> choice;
		}

		//--------qty---------------//
		cout << "Quantity" << endl << "> ";
		istr >> this->qty;
		while ((this->qty <= 0 || this->qty > MAX_STOCK_NUMBER) || istr.fail()) {
			this->err = ERROR_POS_QTY;
			if (istr.fail()) {
				istr.clear();
				istr.ignore(123, '\n');
				cout << this->err << endl;
				cout << "> ";
				istr >> this->qty;
			}
			else {
				cout << this->err << endl;
				cout << "> ";
				istr >> this->qty;
			}
		}
		delete[] tmp;
		return istr;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const {
		if (err) {
			cerr << this->type << "," << this->SKU << "," << this->name << "," << this->price << "," << this->taxed
				<< "," << this->qty;
		}
		else {
			ofstr << ((this->type == 1) ? "T" : "") << "," << this->SKU << "," << this->name << "," << fixed << setprecision(2) <<this->price << "," << this->taxed
				<< "," << this->qty;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		this->err.clear();
		char comma{};
		char* SKU{};
		char* name{};
		double price{};
		int taxed{};
		int qty{};
		SKU = dynRead(ifstr, ',');
		name = dynRead(ifstr, ',');
		ifstr >> price >> comma >> taxed >> comma >> qty;
		if (ifstr.fail()) {}
		else {
			if (strLen(SKU) <= 7) {
				strCpy(this->SKU, SKU);
				if (strLen(name) <= 40) {
					delAlloCopy(this->name, name);
					if (price >= 0) {
						this->price = price;
						this->taxed = taxed;
						if (qty > 0 && qty <= MAX_STOCK_NUMBER) {
							this->qty = qty;
						}
						else {
							this->err = ERROR_POS_QTY;
						}
					}
					else {
						this->err = ERROR_POS_PRICE;
					}
				}
				else {
					this->err = ERROR_POS_NAME;
				}
			}
			else {
				this->err = ERROR_POS_SKU;
			}
		}
		delete[] SKU; delete[] name;
		return ifstr;

	}

	Item::Item() {
		this->err = {};
		this->name = nullptr;
		this->SKU[0] = '\0';
		this->price = 0.0;
		this->qty = 0;
		this->taxed = false;
		//this->type = 1;
	}

	Item::~Item() {
		delete[] this->name;
		this->name = nullptr;
		this->SKU[0] = '\0';
	}

	Item::Item(const Item& rhs) {
		*this = rhs;
	}

	Item& Item::operator=(const Item& rhs) {
		if (this != &rhs) {
			//1. Clean-up
			//delete[] this->name;
			this->SKU[0] = '\0';

			//2. Shallow cpy
			this->price = rhs.price;
			this->taxed = rhs.taxed;
			this->qty = rhs.qty;
			this->type = rhs.type;
			strCpy(this->SKU, rhs.SKU);

			//Deep Copy
			if (rhs.name != nullptr) {
				//Ensure name is safe for strlen
				delAlloCopy(this->name, rhs.name);
				/*this->name = new char[strLen(rhs.name) + 1];
				this->name = rhs.name;*/
			}
			else {
				this->name = nullptr;
			}
		}
		return *this;
	}

	std::ostream& Item::bprint(std::ostream& ostr) const
	{
		if (strLen(this->name) > 20) {
			ostr << "| ";
			for (auto i = 0; i < 20; i++) {
				ostr << this->name[i];
			}
			ostr << "|";
			ostr << right << "    " << this->cost() << " | " << ((this->taxed) ? " T  " : "    ") << "|" << endl;
			}
			else {
				ostr << "| " << setw(20) << left << this->name << "|     " << right << this->cost() << " | " << ((this->taxed) ? " T  " : "    ") << "|" << endl;

			}

		return ostr;
	}

	bool Item::operator==(const char* rhs) const {
		if (strcmp(this->SKU, rhs) == 0) {
			return true;
		}
		return false;
	}

	bool Item::operator>(const Item& rhs) const
	{
		if (this->name[0] > rhs.name[0]) {
			return true;
		}
		return false;
	}

	int Item::operator+=(const int& rhs)
	{
		this->qty += rhs;
		if (this->qty > MAX_STOCK_NUMBER) {
			this->qty = MAX_STOCK_NUMBER;
			this->err = ERROR_POS_QTY;
		}
		return this->qty;
	}

	int Item::operator-=(const int& rhs) {
		if (rhs > this->qty) {
			this->qty = 0;
			this->err = ERROR_POS_STOCK;
		}
		else {
			this->qty -= rhs;
		}

		return this->qty;
	}

	Item::operator bool() const {
		return !(this->err);
	}

	double operator+=(double& lhs,Item& rhs) {
		return rhs.quantity() * rhs.cost() + lhs;
	}

}