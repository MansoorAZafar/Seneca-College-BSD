// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 10, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#include <iostream>
#ifndef SICT_VALIDATE_H_
#define SICT_VALIDATE_H_
namespace sict {
    template <typename A, typename B>
    //arr2 is a bool array
    bool validate(const A& minVal, const B* arr, int len, bool* arr2) {
        int goodCount = 0;
        for (auto i = 0; i < len; i++) {
            if (arr[i] >= minVal) {
                goodCount++;
                arr2[i] = true;
            }
            else {
                arr2[i] = false;
            }
        }
        return goodCount == len;
    }

}
#endif