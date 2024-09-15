#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class Perishable : public Item {
		Date date{};
	public:
		char itemType() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
	};
}
#endif