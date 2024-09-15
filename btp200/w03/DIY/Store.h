#ifndef SDDS_STORE_H
#define SDDS_STORE_H
#define MAX_SNAME 31
#define MAX_NUM_TOYS 10
#include "Toys.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	class Store {
	private:
		char m_sName[MAX_SNAME];
		int m_noOfToys = 0;
		int m_addToys = 0;
		Toys m_toy[MAX_NUM_TOYS];
	public:
		void setStore(const char* sName, int no);
		void setToys(const char* tname, int sku, double price, int age);
		void display()const;
		void find(int sku);
		void setEmpty();
	};

}


#endif // !