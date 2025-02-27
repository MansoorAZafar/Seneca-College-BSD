/* Citation and Sources...
Final Project Milestone 2
Module: PosApp
Filename: PosApp.h
Version 1.0
Author	Mansoor Zafar
Revision History
-----------------------------------------------------------
Date      Reason
2023/03/15  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 25, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include <iostream>
#define TAX 0.13
#define MAX_SKU_LEN 7
#define MIN_YEAR 2000
#define MAX_YEAR 2030
#define MAX_STOCK_NUMBER 99
#define MAX_NO_ITEMS 2000

namespace sdds {
	class PosApp {
		char filename[255] = {};
		// client doesn't need access to these functions
		std::istream& takeInput(std::istream& istr, int& val);
		void save();
		void menu();
		void setEmpty();
		void listItems() const;
		void addItem();
		void removeItem();
		void stockItem();
		void pointOfSale();
		std::ostream& exit(std::ostream& ostr = std::cout);
	public:
		PosApp();
		PosApp(const char* filename);
		~PosApp();
		void run();
		PosApp(const PosApp&) = delete; // Prevent copying constructor
		PosApp& operator=(const PosApp& rhs) = delete; // Prevent Copying assignment
	};
}

#endif // !SDDS_POSAPP_H
