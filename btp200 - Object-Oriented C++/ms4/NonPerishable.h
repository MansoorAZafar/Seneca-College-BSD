#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#include "Item.h"
namespace sdds {
	class NonPerishable : public Item {
	public:
		char itemType() const;
		std::ostream& write(std::ostream& ostr) const;
	};
}

#endif