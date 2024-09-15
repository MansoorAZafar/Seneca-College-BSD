#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H
#include <iostream>
#include "Cheese.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	class CheeseParty
	{
	private:
		const sdds::Cheese** m_pCheeses{};
		size_t m_cnt{};

	public:
		CheeseParty();
		CheeseParty& addCheese(const Cheese& rhs);
		CheeseParty& removeCheese();
		~CheeseParty();

		size_t getCount() const;
		std::ostream& print(std::ostream& ostr) const;

		CheeseParty(const CheeseParty& rhs);
		CheeseParty& operator=(const CheeseParty& rhs);

		CheeseParty(CheeseParty&& rhs);
		CheeseParty& operator=(CheeseParty&& rhs);

	};
	std::ostream& operator<<(std::ostream& ostr, const CheeseParty& rhs);
}

#endif

