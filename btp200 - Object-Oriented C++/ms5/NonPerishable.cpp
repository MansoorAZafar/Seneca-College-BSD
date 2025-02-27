// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#include <iostream>
#include "NonPerishable.h"
using namespace std;
namespace sdds {

    char NonPerishable::itemType() const {
        return 'N';
    }

    std::ostream& NonPerishable::write(std::ostream& ostr) const
    {
        if (*this) {
            Item::write(ostr);
            if (this->type == POS_LIST) {
                ostr << "     N / A   |"; //im fine

            }
            else {
                ostr << "=============^" << endl;
            }
        }
        return ostr;
    }
}