#ifndef SDDS_VIDEO_H
#define SDDS_VIDEO_H
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "Media.h"

namespace sdds {
	class Video : public Media {
		int m_length = 0; // length of video
	protected:
		int get() const;
	public:
		Video();
		Video(int);
		Video(const Video& rhs) = delete;
		Video& operator=(const Video& rhs) = delete;
		void load(std::istream& istr);
		void setEmpty();
	};
}

#endif