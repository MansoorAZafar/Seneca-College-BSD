// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include <iostream>
#include <cstring>
#include "Animation.h"

using namespace std;
namespace sdds {
	sdds::Animation::Animation() : Video()
	{
		this->m_dimension = 0;
	}

	sdds::Animation::Animation(int length, int dimension) : Video(length)
	{
		if (dimension < 4 && dimension > 1) {
			this->m_dimension = dimension;
		}
		else {
			this->m_dimension = 0;
			this->setEmpty();
		}
	}

	void sdds::Animation::load(std::istream& istr)
	{
		Video::load(istr);
		istr >> this->m_dimension;
		if (this->m_dimension >= 4 || this->m_dimension <= 1) {
			this->m_dimension = 0;
		}
		istr.clear();
		istr.ignore();
	}

	std::ostream& sdds::Animation::play(std::ostream& ostr) const
	{
		if ((this->m_dimension == 2 || this->m_dimension == 3) && this->get() > 0) {
			ostr << "Animation is in " << this->m_dimension << "-D" << endl
				<< "Video Length = " << this->get();
		}
		return ostr;
	}

}