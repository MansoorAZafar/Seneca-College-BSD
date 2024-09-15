#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H
#include <iostream>
#include "Cheese.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds 
{

	class CheeseShop
	{
	private:
		const sdds::Cheese** m_pCheeses{};
		std::string m_Shopname{"No Name"};
		size_t m_cnt{};
	public:
		CheeseShop(const std::string& name);
		CheeseShop& addCheese(const Cheese&);
		~CheeseShop();
		std::string getShopName() const;
		size_t getCount() const;
		std::ostream& print(std::ostream& ostr) const;

		CheeseShop(const CheeseShop& rhs);
		CheeseShop& operator=(const CheeseShop& rhs);

		CheeseShop(CheeseShop&& rhs);
		CheeseShop& operator=(CheeseShop&& rhs);

	};
	std::ostream& operator<<(std::ostream& ostr, const CheeseShop& rhs);

}


#endif

