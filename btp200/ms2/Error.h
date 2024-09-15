#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 25, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds{
	class Error{
		char* error_message_pointer = nullptr;
	public:
		Error(); // default constructor 
		//Constructor + arg
		Error(const char* msg);
		//Destructor
		~Error();
		//Copy Constructor
		Error(const Error&);
		//Copy Assignment
		Error& operator=(const Error& rhs); 
		//Assignment to C-String
		Error& operator=(const char*);
		//Boolean type conversion
		operator bool() const;
		Error& clear();
		const char* getMessage() const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Error& rhs);
}
#endif

