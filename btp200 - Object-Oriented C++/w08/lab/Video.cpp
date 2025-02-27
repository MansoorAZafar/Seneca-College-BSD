// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "Video.h"

using namespace std;
namespace sdds {

    int sdds::Video::get() const
    {

        return this->m_length;
    }

    sdds::Video::Video()
    {
        this->m_length = 0;
    }

    sdds::Video::Video(int val)
    {
        if (val >= 0) {
            this->m_length = val;
        }
        else {
            this->m_length = 0;
        }
    }

    void sdds::Video::load(std::istream& istr)
    {
        char comma;
        istr >> this->m_length >> comma;
        if (this->m_length <= 0) {
            this->m_length = 0;
        }
    }

    void sdds::Video::setEmpty() {
        this->m_length = 0;
    }
}