#define _CRT_SECURE_NO_WARNINGS
#include "Tools.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
    void strCpy(char* str1, const char* str2) {
        while (*str2) {
            *str1++ = *str2++;
        }
        *str1 = 0;
    }
    //Added: 
    int strLen(const char* str) {  // Fully provided
        int i = -1;
        while (str[++i]);
        return i;
    }

}