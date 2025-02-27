#ifndef SDDS_ANIMATION_H
#define SDDS_ANIMATION_H
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "Video.h"
namespace sdds {
	class Animation : public Video {
		int m_dimension = 0;
	public:
		Animation();
		Animation(int, int);
		void load(std::istream& istr);
		std::ostream& play(std::ostream& ostr) const;
	};
}
#endif