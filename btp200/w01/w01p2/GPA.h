/***********************************************************************
// OOP244 Workshop 1 p2: GPA header file
//
// File  GPA.h
// Version 1.0
// Date  winter 2023
// Author Fardad Soleimanloo
//
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 

#ifndef SDDS_GPA_H
#define SDDS_GPA_H


struct GPA {
    char name[116];
    double gpa;
    int stno;
};

#endif // !SDDS_GPA_H