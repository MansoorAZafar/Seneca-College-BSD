#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Date.h"
#include "POS.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 24, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds {
    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int uniqueDateValue(int year, int mon, int day, int hour, int min) {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int daysOfMonth(int year, int month) {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    /*
    Legend:
    return -1 = year is bad
    return -2 = month is bad
    return -3 = day is bad
    return -4 = hour is bad
    return -5 = minute is bad
    return 1 = all good
    */
    int sdds::Date::valid() const
    {
        if (this->year >= MIN_YEAR && this->year <= MAX_YEAR) {
            if (this->month >= 1 && this->month <= 12) {
                if (this->day >= 1 && this->day <= daysOfMonth(this->year, this->month)) {
                    if (this->hour >= 0 && this->hour <= 23) {
                        if (this->minute >= 0 && this->minute <= 59) {
                            return 1;
                        }
                        else {
                            return -5;
                        }
                    }
                    else {
                        return -4;
                    }
                }
                else {
                    return -3;
                }
            }
            else {
                return -2;
            }
        }
        else {
            return -1;
        }
    }

    Date::Date()
    {
        getSystemDate(this->year, this->month, this->day, this->hour, this->minute, this->flag);
    }

    Date::Date(int year, int month, int day, int hour, int minute)
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->flag = false;
        if (this->valid()) {

        }
        else {
            err.operator=("Bad");
        }
    }

    bool Date::operator==(const Date& rhs) const
    {
        if (this->year == rhs.year) {
            if (this->month == rhs.month) {
                if (this->day == rhs.day) {
                    if (this->hour == rhs.hour) {
                        if (this->minute == rhs.minute) {
                            if (this->flag == rhs.flag) {
                                if (this->err == rhs.err) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool Date::operator!=(const Date& rhs) const
    {
        return !(this->operator==(rhs));
    }

    bool Date::operator<(const Date& rhs) const
    {
        if ((this->year < rhs.year) || (this->month < rhs.month) || (this->day < rhs.day) || (this->hour < rhs.hour) || (this->minute < rhs.minute)) {
            return true;
        }
        return false;
    }

    bool Date::operator>(const Date& rhs) const
    {
        return !((*this) < rhs);
    }

    bool Date::operator<=(const Date& rhs) const
    {
        if (this->year <= rhs.year) {
            if (this->month <= rhs.month) {
                if (this->day <= rhs.day) {
                    if (this->hour <= rhs.hour) {
                        if (this->minute <= rhs.minute) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool Date::operator>=(const Date& rhs) const
    {
        if ((*this) == rhs) {
            return true;
        }
        return !((*this) <= rhs);
    }

    Date& Date::dateOnly(bool flag)
    {
        this->flag = flag;
        if (flag) {
            this->hour = 0;
            this->minute = 0;
        }
        return *this;
    }

    /* Date& Date::operator=(Date& rhs)
     {
         if (this != &rhs) {

         }
     }*/

    Date::operator bool() const
    {
        return !(this->err);
    }

    const Error& Date::error() const
    {
        return this->err;
    }

    std::ostream& Date::display(std::ostream& ostr) const
    {
        switch (this->valid()) {
        case -1:
            if (this->flag) {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ")";
            }
            else {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ", " <<
                    ((this->hour < 10) ? "0" : "") << this->hour << ":" << ((this->minute < 10) ? "0" : "") <<
                    this->minute << ")";
            }
            break;
        case -2:
            if (this->flag) {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ")";
            }
            else {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ", " <<
                    ((this->hour < 10) ? "0" : "") << this->hour << ":" << ((this->minute < 10) ? "0" : "") <<
                    this->minute << ")";
            }
            break;
        case -3:
            if (this->flag) {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ")";
            }
            else {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ", " <<
                    ((this->hour < 10) ? "0" : "") << this->hour << ":" << ((this->minute < 10) ? "0" : "") <<
                    this->minute << ")";
            }
            break;
        case -4:
            if (this->flag) {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ")";
            }
            else {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ", " <<
                    ((this->hour < 10) ? "0" : "") << this->hour << ":" << ((this->minute < 10) ? "0" : "") <<
                    this->minute << ")";
            }
            break;
        case -5:
            if (this->flag) {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ")";
            }
            else {
                ostr << this->error() << "(" << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day << ", " <<
                    ((this->hour < 10) ? "0" : "") << this->hour << ":" << ((this->minute < 10) ? "0" : "") <<
                    this->minute << ")";
            }
            break;
        case 1:
            if (this->flag) {
                ostr << this->year << "/" << ((this->month < 10) ? "0" : "") << this->month << "/" << ((this->day < 10) ? "0" : "") << this->day;
            }
            else {
                ostr << this->year << "/" << ((this->month) < 10 ? "0" : "") << this->month << "/" <<
                    ((this->day) < 10 ? "0" : "") << this->day << ", " << ((this->hour < 10) ? "0" : "") <<
                    this->hour << ":" << ((this->minute < 10) ? "0" : "") << this->minute;
            }
            break;
        }
        return ostr;
    }

    Date& Date::set(const int& year, const int& month, const int& day, const int& hour, const int& minute)
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        return *this;
    }

    std::ostream& operator<<(std::ostream& ostr, Date& rhs)
    {
        rhs.display(ostr);
        return ostr;
        // TODO: insert return statement here
    }

    std::istream& operator>>(std::istream& istr, Date& rhs)
    {
        rhs.err.clear();
        bool flag = true;
        char delim = '\0';
        int y = -1;
        int m = -1;
        int d = -1;
        int h = 0;
        int min = 0;
        int count = 0;
        int tmp = 0;
        /*
        Logic:
        Take a number as an input
        IF istr fails (not a number)
        then take it as a delimiter (char)
        IF it is a number go to switch statement
        Set inputted value to respective value (y = 1st inputted m = 2nd inputted ....)
        Increase count value to keep track of which to add upon (month, year, day ...)
        Check if istream is at new line
        IF YES : end the loop
        IF NO  : do nothing
        */
        bool cinOK = true;
        while (flag) {
            istr >> tmp;
            if (istr.fail()) {
                istr.clear();
                istr >> delim;
                if (count == 0 && (((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122))) { y = 0; m = 0; d = 0; h = 0; min = 0; flag = false; cinOK = false; rhs.err.operator=("Cannot read year entry"); }
                if (count == 1 && (((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122))) { y = 1; m = 0; d = 0; h = 0; min = 0; flag = false; cinOK = false; rhs.err.operator=("Cannot read month entry"); }
                if (count == 2 && (((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122))) { y = 1; m = 1; d = 0; h = 0; min = 0; flag = false; cinOK = false; rhs.err.operator=("Cannot read day entry"); }
                if (count == 3 && (((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122))) { y = 1; m = 1; d = 1; h = 0; min = 0; flag = false; cinOK = false; rhs.err.operator=("Cannot read hour entry"); }
                if (count == 4 && (((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122))) { y = 1; m = 1; d = 1; h = 1; min = 0; flag = false; cinOK = false; rhs.err.operator=("Cannot read minute entry"); }
            }
            else {
                switch (count) {
                case 0: y = tmp; break;
                case 1: m = tmp; break;
                case 2: d = tmp; break;
                case 3: h = tmp; break;
                case 4: min = tmp; break;
                }
                count++;
            }
            if (istr.peek() == '\n' || count >= 5) {
                flag = false;

            }
        }
        /*
            if ((((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122)) && (count == 3)) {
                //if the delimiter is a letter and not a proper delimiter:
                //For error for hours
                h = -1;
                min = -1;
            }
            if ((((int)delim >= 65 && (int)delim <= 90) || ((int)delim >= 97 && (int)delim <= 122)) && (count == 4)) {
                //if the delimiter is a letter and not a proper delimiter:
                //For error for minutes
                h = -1;
                min = -1;
            }
        */
        rhs.set(y, m, d, h, min);
        //Print out respective message
        if (cinOK) {
            switch (rhs.valid()) {
            case -1:
                rhs.err.operator=("Invalid Year");
                break;
            case -2:
                rhs.err.operator=("Invalid Month");
                break;
            case -3:
                rhs.err.operator=("Invalid Day");
                break;
            case -4:
                rhs.err.operator=("Invalid Hour");
                break;
            case -5:
                rhs.err.operator=("Invlid Minute");
                break;
            }
        }
        return istr;
    }

}