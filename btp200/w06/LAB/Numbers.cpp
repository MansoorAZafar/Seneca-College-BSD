#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Numbers.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 10th, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;
namespace sdds {
    void Numbers::sort(double* nums, unsigned int size) {
        unsigned int i, j;
        double temp;
        for (i = size - 1; size && i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (nums[j] > nums[j + 1]) {
                    temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
    }

    unsigned int Numbers::countLines(const char* filename) { /**/
        unsigned int lines = 0u;
        ifstream nums(filename);
        while (nums) {
            lines += (nums.get() == '\n');
        }
        return lines;
    }

    ostream& Numbers::display(ostream& ostr) const {
        if (this->collection_size <= 0) {
            ostr << "Empty list";
            return ostr;
        }
        if (this->originalFlag) {
            ostr << this->filename << endl;
        }
        else {
            ostr << "Copy of " << this->filename << endl;
        }
        for (unsigned int i = 0; i < this->collection_size; i++) {
            ostr.setf(ios::fixed);
            if (i == this->collection_size - 1) { ostr << setprecision(2) << this->collection[i]; }
            else { ostr << setprecision(2) << this->collection[i] << ", "; }
        }
        auto defaultWidth = ostr.width(86); auto defaultFill = ostr.fill('-'); ostr << endl;
        ostr << "\nTotal of " << this->collection_size << " number(s), Largest: " << this->max() << ", Smallest: " << this->min() << ", Average: " << this->average();
        ostr.width(76); ostr.fill('='); ostr << endl;
        ostr << "";
        ostr.fill(defaultFill); ostr.width(defaultWidth);
        return ostr;
    }

    Numbers::Numbers(const char* filename) {
        if (filename != nullptr) {
            strcpy(this->filename, filename);
            this->load();
        }
        else {

            this->setEmpty();

        }
    }
    Numbers::Numbers() {
        this->setEmpty();
    }
    Numbers::~Numbers() {
        this->save();
        delete[] this->collection;
    }
    Numbers::Numbers(Numbers& rhs) {
        if (this) {
            this->save();
            *this = rhs;
        }
    }
    Numbers& Numbers::operator=(Numbers& rhs) {
        //fix for self assessment
        if (this != &rhs) {
            this->save(); // step 1
            this->setEmpty(); // step 3
            if (rhs.collection_size > 0) {
                strcpy(this->filename, rhs.filename);
                this->originalFlag = false;
                this->collection = new double[rhs.collection_size];
                for (unsigned int i = 0; i < rhs.collection_size; i++) {
                    this->collection[i] = rhs.collection[i];
                }
                this->collection_size = rhs.collection_size;
            }
        }
        return *this;
    }
    void Numbers::sort() {
        this->sort(this->collection, this->collection_size);
    }

    //======== Set all attributes to null, zero, false or empty Cstring =========
    void Numbers::setEmpty() {
        delete[] this->collection;
        this->collection = nullptr;
        this->filename[0] = '\0';
        this->collection_size = 0;
        this->originalFlag = true;
        this->addedFlag = false;
    }
    //========
    bool Numbers::load() {
        auto size = this->countLines(this->filename);
        if (size > 0) {
            ifstream ifs(this->filename);
            double* temp = new double[size];
            unsigned int index = 0;
            double tmp = 0.0;
            while (ifs) {
                ifs >> tmp;
                if (ifs) {
                    if (index < size) {
                        temp[index] = tmp;
                        index++;
                    }
                    tmp = 0;
                }
            }
            delete[] this->collection;

            this->collection = temp;
            if (index == size) {
                this->collection_size = index;
            }
            else {
                this->setEmpty();
            }
        }
        if (this->collection_size > 0) {
            this->originalFlag = true;
            return true;
        }
        return false;
    }
    void Numbers::save() {
        if (this->originalFlag && this->addedFlag) {
            ofstream osf(this->filename);
            osf.setf(ios::fixed);
            osf.precision(2);
            for (unsigned int i = 0; i < this->collection_size; i++) {
                osf << this->collection[i] << endl;
            }
        }
    }
    double Numbers::max() const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < this->collection_size; i++) {
            if (this->collection[index] < this->collection[i]) {
                index = i;
            }
        }
        return this->collection[index];
    }
    double Numbers::min() const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < this->collection_size; i++) {
            if (this->collection[index] > this->collection[i]) {
                index = i;
            }
        }
        return this->collection[index];
    }
    Numbers::operator bool() const {
        if (this->collection != nullptr) {
            return true;
        }
        return false;
    }
    double Numbers::average() const {
        auto avg = 0.0;
        for (unsigned int i = 0; i < this->collection_size; i++) {
            avg += this->collection[i];
        }
        avg /= this->collection_size;
        return avg;
    }
    Numbers& Numbers::operator+=(const double val) {
        if(this){
            int size = this->collection_size + 1;
            double* tmp = new double[size];
            for (unsigned int i = 0; i < this->collection_size; i++) {
                tmp[i] = this->collection[i];
            }
            tmp[this->collection_size] = val;
            delete[] this->collection;
            this->collection = tmp;
            this->collection_size = size;
            this->addedFlag = true;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& ostr, Numbers& num) {
        num.display(ostr);
        return ostr;
    }
    std::istream& operator>>(std::istream& istr, Numbers& num) {
        double tmp = 0.0;
        while (istr) {
            istr >> tmp;
            if (istr) {
                num += tmp;
            }
        }
        return istr;
    }

}

/*
*   *ALL RESOLVED NOW*
*
*   ISSUE:
*   1)  Cannot get 'lowest' or highest value since you need to call sort
*   Display cannot call min or max without them being const
*   Neither min nor max can call sort since sort is not const
*   Sort cannot be const
*
*   2)  Only for Test 1, there is an extra space (EXISTS NO WHERE ELSE NOT WITH ANY OTHER TESTS)
*
*   3) What's up with the output file? Last part and last 'text' being 'outputted' to the screen
*   How do I connect numbers.txt to it
*   Check correct_output.txt the very last output/text for better understanding of what im referrering to
*
*   4) The 101 ln in main test 3 f(x) adds an extra lines
*   this one :
*   output << N << endl;
*   I DONT KNOW WHY
*
*   5) Similar to #4
*   ln 49 in main f(x)
*   displayFile("output.txt", false);
*   idk how im supposed to display the information from numebrs.txt
*
*
*   EDITORS NOTE:
*   I FIXED THE SPACING AND #2
*   BOTH #1 AND #2 ARE FIXED
*
*
*/