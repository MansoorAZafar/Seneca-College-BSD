#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>
// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-11-17
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

//Edited on : 2023-11-28 : added comments

namespace sdds
{
	class Utilities
	{
	private:
		//instance variable(s)
		size_t m_widthField{ 1 }; // default value is 1 
		//class variable(s)
		static char m_delimiter;  // delimiter for all class's

		// This function removes whitespace from the front and back of a string
		void trim(std::string& str);

	public:

		//Mutator/Modifiers
		// This function sets the m_widthField attribute
		void setFieldWidth(size_t newWidth);

		// This function sets the m_delimiter attribute for all instances of this class
		static void setDelimiter(char newDelimiter);

		//Accessor/Queries
		// This function returns the m_widthField attribute
		size_t getFieldWidth() const;

		// This function returns the m_delimitier attribute
		static char getDelimiter();

		//Manager/Special
		// This constructor initalizes utilities with 0 parameters with default values
		Utilities() = default;

		//Others
		// This function returns a string from [next_pos, first_occurance_of_delimiter)
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more); //extracts a token from string str referred to by the first parameter.
	};
}

#endif