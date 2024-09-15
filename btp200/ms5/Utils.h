/***********************************************************************
// OOP244 Workshop 9:
// File	Utils.h
// Version 1.0
// Date	Winter of 2023
// Author	Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>
#include <fstream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	int strLen(const char* str);
	void strCpy(char* des, const char* src);
	void strCat(char* des, const char* src);
	void delAlloCopy(char*& des, const char* src);
	char* dynRead(std::istream& istr, char delimeter = '\n');
}
#endif // !