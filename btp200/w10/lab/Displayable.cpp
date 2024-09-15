/***********************************************************************
// OOP244 Workshop 10:
// File	Displayable.cpp
// Version 1.0
// Date	Winter of 2023
// Author	Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Data            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 10, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include "Displayable.h"
namespace sict {
    std::ostream& operator<<(std::ostream& os, const Displayable& D) {
        return D.display(os);
    }
}