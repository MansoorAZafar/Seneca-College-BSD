#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Error.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 25, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds {

	Error::Error()
	{
		this->error_message_pointer = nullptr; // null = no error
	}
	Error::Error(const char* msg)
	{	
		*this = msg;
	}
	Error::~Error()
	{
		delete[] this->error_message_pointer;
	}
	Error::Error(const Error& rhs)
	{
		this->error_message_pointer = nullptr;
		*this = rhs;
	}
	Error& Error::operator=(const Error& rhs)
	{
		if (this != &rhs) {
			//1. Clean up:
			delete[] this->error_message_pointer;
			//Ensure rhs error name isnt null so it won't break strcpy
			if (rhs.error_message_pointer == nullptr) {
				this->clear();
			}
			else {
				//If safe: Deep copy:
				this->error_message_pointer = new char[strlen(rhs.error_message_pointer) + 1]; // dynamically allocate memory for error msg
				strcpy(this->error_message_pointer, rhs.error_message_pointer); // copy the 
			}	
		}
		return *this; // return a copy of the current obj
	}
	Error& Error::operator=(const char* msg)
	{
		if (msg != nullptr) {
			this->error_message_pointer = new char[strlen(msg) + 1]; // dynamically allocate memory for the error msg
			strcpy(this->error_message_pointer, msg); // copy it into the now dynamicaly allocated error message
		}
		else {
			return this->clear(); // return an empty error message
		}
		return *this;
	}
	Error::operator bool() const
	{
		if (this->error_message_pointer != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	Error& Error::clear()
	{
		delete[] this->error_message_pointer;
		this->error_message_pointer = nullptr;
		return *this;
	}
	const char* Error::getMessage() const
	{
		if (this->error_message_pointer) {
			return this->error_message_pointer;
		}
		else {
			return "";
		}
		
	}
	std::ostream& operator<<(std::ostream& ostr, const Error& rhs)
	{
		ostr << rhs.getMessage();
		return ostr;
	}
}
