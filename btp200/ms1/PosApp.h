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

#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 15, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class PosApp {
		char filename[255] = {};
		

	public:
		PosApp();
		PosApp(const char* filename);
		~PosApp();
		void run();
		void menu();
		void setEmpty();
		std::istream& takeInput(std::istream& istr, int& val);
		void listItems() const;
		void addItem();
		void removeItem();
		void stockItem();
		void pointOfSale();
		std::ostream& exit(std::ostream& ostr = std::cout);
		void save();
		PosApp& operator=(PosApp& rhs);

	};
}

#endif // !SDDS_POSAPP_H
