// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds {
	class Perishable : public Item {
		Date date{};
	public:
		char itemType() const override;
		std::ostream& write(std::ostream& ostr) const override;
		std::istream& read(std::istream& istr) override;
		std::ofstream& save(std::ofstream& ofstr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
	};
}
#endif