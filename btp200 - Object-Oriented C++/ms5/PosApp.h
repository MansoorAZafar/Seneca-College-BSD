// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

/* Citation and Sources...
Final Project Milestone 1
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
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include <iostream>
#include <fstream>
#include "Item.h"
#include "Bill.h"


namespace sdds {
	class PosApp {
		char filename[128]{};
		Item* iptr[MAX_NO_ITEMS]{};
		int nptr{};
		// client doesn't need access to these functions
		std::istream& takeInput(std::istream& istr, int& val, const int& rangeL, const int& rangeH, const char* msg = "");

		void loadRecs();

		Bill bill;
		void save();
		void menu();
		void setEmpty();
		std::ostream& listItems(std::ostream& ostr = std::cout);
		std::ostream& addItem(std::ostream& ostr = std::cout, std::istream& istr = std::cin);
		void removeItem();
		void stockItem();
		void POS();
		int selectItem(const char* msg = "", std::ostream& ostr = std::cout);
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