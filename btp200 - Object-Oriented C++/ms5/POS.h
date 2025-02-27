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

#ifndef SDDS_POS_H
#define SDDS_POS_H




namespace sdds {
#define TAX 0.13
#define MAX_SKU_LEN 7
#define MIN_YEAR 2000
#define MAX_YEAR 2030
#define MAX_STOCK_NUMBER 99
#define MAX_NO_ITEMS 200//could be 2000
#define MAX_NAME_LEN 40

#define POS_LIST  1
#define POS_FORM  2

#define  ERROR_POS_SKU "SKU too long"
#define ERROR_POS_NAME  "Item name too long"
#define ERROR_POS_PRICE  "Invalid price value"
#define ERROR_POS_TAX  "Invalid tax status"
#define ERROR_POS_QTY  "Invalid quantity value"
#define ERROR_POS_STOCK  "Item out of stock"
#define ERROR_POS_EMPTY  "Invalid Empty Item"

	//Define works but const doesn't GeE gEe

	//const double TAX = 0.13;
	//const int MAX_SKU_LEN = 7;
	//const int MIN_YEAR = 2000;
	//const int MAX_YEAR = 2030;
	//const int MAX_STOCK_NUMBER = 99;
	//const int MAX_NO_ITEMS = 200;//could be 2000
	//const int MAX_NAME_LEN = 40;

	//const int POS_LIST = 1;
	//const int POS_FORM = 2;

	//const char* ERROR_POS_SKU = "SKU too long";
	//const char* ERROR_POS_NAME = "Item name too long";
	//const char* ERROR_POS_PRICE = "Invalid price value";
	//const char* ERROR_POS_TAX = "Invalid tax status";
	//const char* ERROR_POS_QTY = "Invalid quantity value";
	//const char* ERROR_POS_STOCK = "Item out of stock";
	//const char* ERROR_POS_EMPTY = "Invalid Empty Item";
}

#endif // !SDDS_POSAPP_H