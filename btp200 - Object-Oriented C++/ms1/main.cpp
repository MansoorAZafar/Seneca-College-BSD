// Final Project Milestone 2
// Student POS App Mockup tester
// Version 1.0
// Date	2023-02-28
// Author	Fardad Soleimanloo
// Description
// This program test the student implementation of the PosApp class
// for submission.
//
/////////////////////////////////////////////////////////////////
#include "PosApp.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 15, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

int main() {
	sdds::PosApp pos("datafile.csv");
	pos.run();
	return 0;
}