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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;
#include "Utils.h"
namespace sdds {
    int strLen(const char* str) {
	if(str == nullptr){return -1;}
        int len = -1;
        while (str[++len]);
        return len;
    }
    void strCpy(char* des, const char* src) {
        while (*src) *des++ = *src++;
        *des = *src;
    }
    void strCat(char* des, const char* src) {
        while (*des) des++;
        while (*src) *des++ = *src++;
        *des = *src;
    }
    void delAlloCopy(char*& des, const char* src) {
        delete[] des;
        des = nullptr;
        if (src && src[0]) {
            des = new char[strLen(src) + 1];
            strCpy(des, src);
        }
    }
    char* dynRead(istream& istr, char delimeter) {
        char* str{};
        string toRead;
        getline(istr, toRead, delimeter);
        if (istr) {
            str = new char[strLen(toRead.c_str()) + 1];
            strCpy(str, toRead.c_str());
        }
        return str;
    }
}