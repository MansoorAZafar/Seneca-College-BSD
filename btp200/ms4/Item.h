#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class Item : public PosIO {
		char SKU[MAX_SKU_LEN]{};
		char* name{};
		double price{};
		bool taxed{};
		int qty{};

		//Mem f(x)
		Item& clear();
	protected:
		int type{};
		Error err{};
	public:
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		virtual char itemType() const = 0;
		double cost() const;
		int quantity() const;
		Item& displayType(int);
		//Constructor 
		Item();
		//Rule of 3
		~Item();
		Item(const Item& rhs);
		Item& operator=(const Item& rhs);
		//Mem operators
		std::ostream& bprint(std::ostream& ostr) const;
		bool operator==(const char* rhs) const;
		bool operator>(const Item& rhs) const;
		int operator+=(const int& rhs);
		int operator-=(const int& rhs);
		operator bool() const;


	};
	double operator+=(double& lhs, Item& rhs);
}
#endif // !SDDS_POSAPP_H