// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 16, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

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
#include <fstream>
#include <iomanip>
#include "PosApp.h"
#include "Utils.h"
#include "Perishable.h"
#include "NonPerishable.h"
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | April 4, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;
namespace sdds {

	//================== Running Entire Program f(x) ==================//

	//Compiles everything together
	void PosApp::run() {
		//Printing basic info:
		this->loadRecs();
		//Start program
		this->menu();
	}

	//Prints out the 6 options
	const ostream& printMenu(ostream& ostr = cout) {
		ostr << "The Sene-Store" << endl
			<< "1- List items" << endl
			<< "2- Add item" << endl
			<< "3- Remove item" << endl
			<< "4- Stock item" << endl
			<< "5- POS" << endl
			<< "0- exit program" << endl
			<< "> ";
		return ostr;
	}

	//Combines the menu options + input into 1 function
	void PosApp::menu() {
		printMenu(); // Print the menu options
		int choice = 0; // made to store the input	: Used for the switch statement
		this->takeInput(cin, choice, 0, 5);
		while ((choice) != 0) {
			switch (choice) {
			case 1: this->listItems();		printMenu();		this->takeInput(cin, choice, 0, 5); break; // if they select 1		: follow up with the listItems f(x)		: print menu 
			case 2: this->addItem();		printMenu();		this->takeInput(cin, choice, 0, 5); break; // if they select 2		: follow up with the addItem f(x)		: print menu 
			case 3: this->removeItem();		printMenu();		this->takeInput(cin, choice, 0, 5); break; // if they select 3		: follow up with the removeItem f(x)	: print menu 
			case 4: this->stockItem();		printMenu();		this->takeInput(cin, choice, 0, 5); break; // if they select 4		: follow up with the stockItem f(x)		: print menu
			case 5: this->POS();	printMenu();		this->takeInput(cin, choice, 0, 5); break; // if they select 5	: follow up with the pointOfSale f(x)	: print menu
				// take input again 
			}
		}
		exit(cout); //If they select 0	: follow up with the exit f(x)
	}

	//================== END OF Running Entire Program f(x) ==================//


	//================== TAKING INPUT ==================//

	istream& PosApp::takeInput(istream& istr, int& val, const int& rangeL, const int& rangeH, const char* msg) {
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
			else if ((val < rangeL || val > rangeH)) {
				//if value is outside of given range
				cout << "[" << rangeL << "<=value<=" << rangeH << "], retry: " << msg;
			}
			else {
				//value is acceptable	: leave while loop
				flag = false;
			}
		}
		return istr; // return a good inputted value 
	}

	//================== READING FROM FILE (loadRecs f(x)) =====================//

	void PosApp::loadRecs() {
		//Legend:
		// 1. Print out action title
		// 2. open file in an ifstream called Input
		// 2.5: IF cannot open, using ofstream open and close the filename
		// 3. 
		//
		cout << ">>>> Loading Items..........................................................." << endl;
		//cout << "Loading data from " << this->filename << endl;

		ifstream input(this->filename);
		if (input) {
			char type, comma;
			for (auto i = 0; i < this->nptr; i++) {
				if (this->iptr[this->nptr] != nullptr) {
					delete this->iptr[i];
				}
				this->iptr[i] = nullptr;
			}
			while (input && this->nptr < MAX_NO_ITEMS) {
				input >> type >> comma;
				if (type == 'P') {
					iptr[nptr] = new Perishable();
					iptr[nptr]->load(input);
					this->nptr++;
				}
				else if (type == 'N') {
					iptr[nptr] = new NonPerishable();
					iptr[nptr]->load(input);
					this->nptr++;
				}
				type = ' ';
			}
		}
		else {
			ofstream filename(this->filename);
			filename.close();
		}
	}


	//================= END OF loadRecs f(x) ==================================//



	//================== END OF TAKING INPUT ==================//


	//================== RUNNING THE GIVEN OPTIONS 0-5 ==================//

	ostream& PosApp::exit(ostream& ostr) {
		this->save(); // run the save f(x)
		ostr << "Goodbye!" << endl; // print msg
		return ostr; // end program
	}

	void PosApp::save() {
		cout << ">>>> Saving Data............................................................." << endl; //<<
		//"Saving data in " << this->filename << endl; // print msg
		ofstream filename(this->filename); // CREATE instance of DATA

		for (auto i = 0; i < this->nptr; i++) {
			this->iptr[i]->save(filename);
			filename << endl;
		}
	}

	std::ostream& PosApp::listItems(std::ostream& ostr) {
		/*
		ISSUE HERE:
		IN ITEM.CPP THE OPERATOR > IS FLAWED
		IT NEEDS TO CHECK FOR ENTIRE STRING NOT JUST 1ST LETTER

		*/


		double cost{};
		ostr << ">>>> Listing Items..........................................................." << endl;
		// << "Running listItems()" << endl; // print msg
		ostr << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl <<
			"-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		for (auto i = 0; i < this->nptr - 1; i++) {
			for (auto j = 0; j < this->nptr - 1; j++) {
				if (this->iptr[j]->operator>(this->iptr[j + 1])) {
					//swap
					Item* tmp = this->iptr[j + 1];
					this->iptr[j + 1] = this->iptr[j];
					this->iptr[j] = tmp;
				}
			}
		}
		for (auto i = 0; i < this->nptr; i++) {
			ostr << right << setw(4) << i + 1 << " | ";
			this->iptr[i]->write(ostr);
			ostr << endl;

			cost += this->iptr[i]->quantity() * this->iptr[i]->cost();
		}


		ostr << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl <<
			"				      Total Asset : $ |" << cost << "| " << endl <<
			"-----------------------------------------------^--------------^" << endl << endl;
		return ostr;
	}

	ostream& PosApp::addItem(ostream& ostr, istream& istr) {
		cout << ">>>> Adding Item to the store................................................" << endl; //<<
		//"Running addItem()" << endl; // print msg
		if (this->nptr == MAX_NO_ITEMS) {
			cout << "Inventory Full!";
			return ostr;
		}
		Item* tmp;
		ostr << "Is the Item perishable? (Y)es/(N)o: ";
		char type;
		istr >> type;
		while (istr.fail() || (type != 'Y' && type != 'y' && type != 'n' && type != 'N')) {
			istr.clear();
			istr.ignore(1000, '\n');
			ostr << type << ", try again...\n";
			istr >> type;

		}
		istr.clear();
		istr.ignore(1000, '\n');
		if (type == 'n' || type == 'N') {
			tmp = new NonPerishable();
		}
		else {
			tmp = new Perishable();
		}
		tmp->read(istr);
		this->iptr[this->nptr] = tmp;
		this->nptr++;
		ostr << ">>>> DONE!..................................................................." << endl;
		return ostr;
	}

	int PosApp::selectItem(const char* msg, ostream& ostr) {
		ostr << ">>>> Item Selection by row number............................................" << endl << "Press <ENTER> to start...." << endl;
		ostr << ">>>> Listing Items..........................................................." << endl;
		ostr << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl <<
			"-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		for (auto i = 0; i < this->nptr - 1; i++) {
			for (auto j = 0; j < this->nptr - 1; j++) {
				if (this->iptr[j]->operator>(this->iptr[j + 1])) {
					//swap
					Item* tmp = this->iptr[j + 1];
					this->iptr[j + 1] = this->iptr[j];
					this->iptr[j] = tmp;
				}
			}
		}
		for (auto i = 0; i < this->nptr; i++) {
			ostr << right << setw(4) << i + 1 << " | ";
			this->iptr[i]->write(ostr);
			ostr << endl;
		}
		ostr << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;

		ostr << "Enter the row number: ";
		int row{};
		this->takeInput(cin, row, 1, this->nptr, msg);
		return row;
	}


	void PosApp::removeItem() {
		cout << ">>>> Remove Item............................................................." << endl;
		int index = this->selectItem("Enter the row number: ") - 1; // to get the index
		cout << "Removing....\n";
		//POS_FORM
		this->iptr[index]->setType(POS_FORM);
		this->iptr[index]->write(cout);
		this->iptr[index]->setType(POS_LIST);

		delete this->iptr[index];
		this->iptr[index] = nullptr;

		for (auto i = index; i < this->nptr; i++) {
			this->iptr[i] = this->iptr[i + 1];
		}
		this->nptr--;


		cout << ">>>> DONE!..................................................................." << endl;
	}

	void PosApp::stockItem() {
		cout << ">>>> Select an item to stock................................................." << endl;
		int index = this->selectItem("Enter the row number: ") - 1;
		//POS_FORM
		this->iptr[index]->setType(POS_FORM);
		cout << "Selected Item:" << endl;
		this->iptr[index]->write(cout);
		this->iptr[index]->setType(POS_LIST);
		cout << "Enter quantity to add: ";
		int qty{};
		this->takeInput(cin, qty, 1, (MAX_STOCK_NUMBER-this->iptr[index]->quantity()), "Enter quantity to add: ");
		cout << ">>>> DONE!..................................................................." << endl;
		this->iptr[index]->operator+=(qty);
	}

	void PosApp::POS() {
		cout << ">>>> Starting Point of Sale.................................................." << endl;
		bool flag = true;
		bool exists = false;
		char SKU[MAX_SKU_LEN]{};
		cin.clear();
		cin.ignore();
		while(flag){
			cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
			if (cin.peek() == '\n') {
				flag = false;
			}
			else {
				char* tmp;
				tmp = dynRead(cin, '\n');
				while (cin.fail() || strLen(tmp) > MAX_SKU_LEN) {
					cin.clear();
					cout << "SKU too long" << endl;
					delete[] tmp;
					tmp = dynRead(cin, '\n');
				}
				strCpy(SKU, tmp);
				for (auto i = 0; i < this->nptr; i++) {
					if (this->iptr[i]->operator==(SKU)) {
						if (this->iptr[i]->quantity() > 0 ) {
							this->iptr[i]->operator-=(1);
							this->iptr[i]->setType(POS_FORM);
							this->iptr[i]->write(cout);
							this->iptr[i]->setType(POS_LIST);
							exists = true;
							cout << endl << ">>>>> Added to bill" << endl;
							bill.add(this->iptr[i]);
							cout << ">>>>> Total: " << bill.total() << endl;
							
						}
						else {
							cout << "Item out of stock" << endl;
							exists = true;
						}
					}
				}
				if (!exists) {
					cout << "!!!!! Item Not Found !!!!!" << endl;
				}
				delete[] tmp;
			}
		}
		bill.print(cout);
	}

	//================== END OF RUNNING THE GIVEN OPTIONS 0-5 ==================//


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
		//delete[] this->iptr; //delete resource
		for (auto i = 0; i < this->nptr; i++) {
			if (this->iptr[i] != nullptr) {
				delete this->iptr[i];
			}
			this->iptr[i] = nullptr;
		}
	}
	//================== END OF CONSTRUCTOR + DESTRUCTORS ==================//


	//================== SET-EMPTY ==================//

	void PosApp::setEmpty() {
		this->filename[0] = '\0'; //Set the filename to an empty state
	}
	//================== END OF SET-EMPTY ==================//
}