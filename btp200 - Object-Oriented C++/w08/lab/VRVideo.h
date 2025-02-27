#ifndef SDDS_VRVIDEO_H
#define SDDS_VRVIDEO_H
#include <iostream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include "Video.h"

namespace sdds {
	class VRVideo : public Video {
		char* m_equipment = nullptr;
	public:
		VRVideo();
		VRVideo(const int, const char*);
		~VRVideo();
		void load(std::istream& istr);
		std::ostream& play(std::ostream& ostr) const;
	};
}
#endif