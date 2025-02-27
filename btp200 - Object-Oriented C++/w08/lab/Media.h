#ifndef SDDS_MEDIA_H
#define SDDS_MEDIA_H
#include <iostream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class Media {
	public:
		virtual ~Media();
		virtual void load(std::istream& istr) = 0;
		virtual std::ostream& play(std::ostream& ostr) const = 0;
	};
	std::ostream& operator<<(std::ostream& ostr, const Media& rhs);
	std::istream& operator>>(std::istream& istr, Media& rhs);
}
#endif