/* Citation and Sources...
Final Project Milestone 1
Module: PosApp
Filename: PosApp.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include "Utils.h"

using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 25, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	//================== Running Entire Program f(x) ==================//

	//Compiles everything together
	void PosApp::run(){
		//Printing basic info:
		cout << ">>>> Loading Items"; auto defaultFill = cout.fill('.'); auto defaultWidth = cout.width(61);
		cout << "\nLoading data from " << this->filename << endl;
		cout.fill(defaultFill); cout.width(defaultWidth); // set fill and width back to default values
		//Start program
		this->menu(); 
	}

	//Prints out the 6 options
	const ostream& printMenu(ostream& ostr = cout){
		ostr << "The Sene-Store" << endl
			<< "1 - List items" << endl
			<< "2 - Add item" << endl
			<< "3 - Remove item" << endl
			<< "4 - Stock item" << endl
			<< "5 - Point of Sale" << endl
			<< "0 - exit program" << endl
			<< "> ";
		return ostr;
	}

	//Combines the menu options + input into 1 function
	void PosApp::menu() {
		printMenu(); // Print the menu options
		int choice = 0; // made to store the input	: Used for the switch statement
		this->takeInput(cin, choice);
		while ((choice) != 0) {
			switch (choice) {
			case 1: this->listItems();		printMenu();		this->takeInput(cin, choice); break; // if they select 1		: follow up with the listItems f(x)		: print menu 
			case 2: this->addItem();		printMenu();		this->takeInput(cin, choice); break; // if they select 2		: follow up with the addItem f(x)		: print menu 
			case 3: this->removeItem();		printMenu();		this->takeInput(cin, choice); break; // if they select 3		: follow up with the removeItem f(x)	: print menu 
			case 4: this->stockItem();		printMenu();		this->takeInput(cin, choice); break; // if they select 4		: follow up with the stockItem f(x)		: print menu
			case 5: this->pointOfSale();	printMenu();		this->takeInput(cin, choice); break; // if they select 5	: follow up with the pointOfSale f(x)	: print menu
				// take input again 
			}
		}
		exit(cout); //If they select 0	: follow up with the exit f(x)
	}
	
	//================== TAKING INPUT ==================//

	istream& PosApp::takeInput(istream& istr, int& val) {
		bool flag = true; // bad val = true
		while (flag) {
			//While the value is bad	: continue loop

			istr >> val; // take input for value
			if (istr.fail()) { 
				//if not an int
				istr.clear(); 
				istr.ignore(123, '\n');
				cout << "Invalid Integer, try again: "; // print msg

			}
			else if ((val < 0 || val > 5)) {
				//if value is outside of given range
				cout << "[0<=value<=5], retry: > ";
			}
			else {
				//value is acceptable	: leave while loop
				flag = false;
			}
		}
		return istr; // return a good inputted value 
	}

	//================== RUNNING THE GIVEN OPTIONS 0-5 ==================//

	ostream& PosApp::exit(ostream& ostr) {
		this->save(); // run the save f(x)
		ostr << "Goodbye!"; // print msg
		return ostr; // end program
	}

	void PosApp::save() {
		cout << ">>>> Saving Data............................................................." << endl <<
			"Saving data in " << this->filename << endl; // print msg

	}

	void PosApp::listItems() const{
		cout << ">>>> Listing Items..........................................................." << endl <<
			"Running listItems()" << endl; // print msg

	}

	void PosApp::addItem() {
		cout << ">>>> Adding Item to the store................................................" << endl <<
			"Running addItem()" << endl; // print msg

	}

	void PosApp::removeItem() {
		cout << ">>>> Remove Item............................................................." << endl <<
			"Running removeItem()" << endl; // print msg

	}

	void PosApp::stockItem() {
		cout << ">>>> Select an item to stock................................................." << endl <<
			"Running stockItem()" << endl; // print msg

	}

	void PosApp::pointOfSale() {
		cout << ">>>> Starting Point of Sale.................................................." << endl <<
			"Running POS()" << endl; // print msg

	}
	
	//================== PREVENT COPYING ==================//
	/*
	PosApp& PosApp::operator=(PosApp& rhs) {
		//If client attempts to copy 
		//! CANNOT BE COPIED !
		return *this; // Regardless of what is trying to be set : Will always be set to itself nothing else
	}
	*/
	//================== CONSTRUCTOR + DESTRUCTORS ==================// 
	//DEFAULT
	PosApp::PosApp() {
		//Should I delete this? 
		//
		// "PosApp is created by receiving the name of a file that is stored in character cString with a maximum length of 255 characters." 
		// Therefore, should there not be a default constructor for no values?
		//----------------------------------------------------------------------------------------------------------------------------------

		this->setEmpty(); // set empty for default values
	}

	//PARAMTER (const char*)
	PosApp::PosApp(const char* filename) {
		if (filename != nullptr) {
			//if the filename is valid	: continue
			strcpy(this->filename, filename); // set the objects filename variable to the given name
		}
		else {
			//If filename is nullptr/bad value
			this->setEmpty(); // set to empty
		}
	}
	
	//DESTRUCTOR
	PosApp::~PosApp() {
		//Not needed rn
	}

	//================== SET-EMPTY ==================//

	void PosApp::setEmpty() {
		this->filename[0] = '\0'; //Set the filename to an empty state
	}

	//================== CONSTRUCTOR + DESTRUCTORS ==================//

}