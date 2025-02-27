#ifndef SDDS_NUMBERS_H_
#define SDDS_NUMBERS_H_
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 10th, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
    class Numbers {
        //Attributes:
        double* collection = nullptr;
        char filename[255] = {};
        unsigned int collection_size = 0;
        bool originalFlag = false;
        bool addedFlag = false;
        //priv member functions
        unsigned int countLines(const char* filename);
        void sort(double* collectionPtr, unsigned int size);
        void setEmpty();
        bool load();
        void save();
        double max() const;
        double min() const;
        double average() const;
    public:
        std::ostream& display(std::ostream& ostr = std::cout) const;
        Numbers(const char* filename);
        Numbers();
        ~Numbers();
        Numbers(Numbers& rhs);
        Numbers& operator=(Numbers& rhs);
        void sort();
        Numbers& operator+=(const double val);
        operator bool() const;
        
    };
    std::ostream& operator<<(std::ostream& ostr, Numbers& num);
    std::istream& operator>>(std::istream& istr, Numbers& num);
}
#endif // !SDDS_NUMBERS_H_
