#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "Tools.h"
#include "Package.h"
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

FILE* fp;
using namespace std;

namespace sdds {


    int openFile_r(const char filename[]) { // Fully provided
        fp = fopen(filename_r, "r");
        return fp != NULL;
    }
    int noOfTraces() {  // Fully provided
        int noOfTraces = 0;
        char ch;
        while (fscanf(fp, "%c", &ch) == 1) {
            noOfTraces += (ch == '\n');
        }
        rewind(fp);
        return noOfTraces;
    }

    // To Do: read functions (4 overloaded read functions)

    char* read(char* str) {
        fscanf(fp, "%60[^\n]\n", str);
        return str;
    }

    bool read(int& data){
        // user_id, dayofyear, Fwifitime and Fctime
        if (fscanf(fp, "%d,", &data)) { return true; }
        return false;
    }

    double& read(double& timeIH) {
        fscanf(fp, "%lf,", &timeIH);
        return timeIH;
    }

    char& read(char& day) {
        if (fscanf(fp, "%[^ \t\n\r\v\f,]%*c,", &day) != 1) {
            day = '\0';
        }
        return day;
    }

    void closefile() { // Fully provided
        if (fp) fclose(fp);
    }

    void strCpy(char* str1, const char* str2) { // Fully provided 
        while (*str2) {
            *str1++ = *str2++;
        }
        *str1 = 0;
    }
    int strLen(const char* str) {  // Fully provided
        int i = -1;
        while (str[++i]);
        return i;
    }
}