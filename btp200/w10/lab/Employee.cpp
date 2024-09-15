/***********************************************************************
// OOP244 Workshop 10:
// File	Employee.cpp
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

#define  _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Employee.h"
namespace sict {

    void Employee::set(int stno, const char* name, double salary) {
        _empno = stno;
        std::strcpy(_name, name);
        _salary = salary;
    }
    Employee::Employee(int stno, const char* name, double salary) {
        set(stno, name, salary);
    }
    std::ostream& Employee::display(std::ostream& os)const {
        return os << _empno << " " << _name << ", " << std::setprecision(2) << std::fixed << _salary;
    }
    bool Employee::operator<=(const Employee& E)const {
        return _empno <= E._empno;
    }
    bool Employee::operator>=(const Employee& E)const {
        return _empno >= E._empno;
    }
    Employee::operator const char* ()const {
        return _name;
    }
}
