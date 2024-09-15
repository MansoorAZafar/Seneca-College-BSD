#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
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

	protected:
		int type{};
		Error err{};
	public:
		Item& clear();
		std::ostream& write(std::ostream& ostr) const override;
		std::istream& read(std::istream& istr) override;
		std::ofstream& save(std::ofstream& ofstr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
		virtual char itemType() const = 0;
		double cost() const;
		int quantity() const;
		Item& displayType(int);
		//Constructor 
		Item();
		//Rule of 3
		virtual ~Item();
		Item(const Item& rhs);
		Item& operator=(const Item& rhs);
		//Mem operators
		std::ostream& bprint(std::ostream& ostr) const;
		bool operator==(const char* rhs) const;
		bool operator>(Item* rhs) const;
		int operator+=(const int& rhs);
		int operator-=(const int& rhs);
		operator bool() const;
		void setType(int);


	};
	double operator+=(double& lhs, Item& rhs);
}
#endif // !SDDS_POSAPP_H