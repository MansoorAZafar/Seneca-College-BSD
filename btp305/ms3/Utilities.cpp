#include <iostream>
#include <string>
#include "Utilities.h"

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
	char Utilities::m_delimiter{};

	//Mutator/Modifiers
	/* This function sets the m_widthField attribute
	* Function: void setFieldWidth
	* param   : size_t 
	* return  : n/a
	*
	*/
	void Utilities::setFieldWidth(size_t newWidth)
	{
		this->m_widthField = newWidth;
	}


	/* Removes whitespace from the front and end of a string
	* Function: void trim
	* param   : string reference
	* return  : n/a
	* 
	*/
	void Utilities::trim(std::string& str)
	{
		auto position = str.find_first_not_of(" ");
		auto endPosition = str.find_last_not_of(" ");
		str = str.substr(position, endPosition - position + 1);
	}


	/* This function sets the m_delimiter attribute for all instances of this class
	* Function: void setDelimiter
	* param   : char 
	* return  : n/a
	*
	*/
	void Utilities::setDelimiter(char newDelimiter)
	{
		Utilities::m_delimiter = newDelimiter;
	}


	//Accessor/Queries
	/* This function returns the m_widthField attribute
	* Function: size_t getFIeldWidth
	* param   : n/a
	* return  : the field width attribute
	*
	*/
	size_t Utilities::getFieldWidth() const
	{
		return this->m_widthField;
	}


	/* This function returns the m_delimitier attribute
	* Function: char getDelimiter
	* param   : n/a
	* return  : a static character repersenting the delimiter
	*
	*/
	char Utilities::getDelimiter()
	{
		return Utilities::m_delimiter;
	}


	//Others
	/* This function returns a sub-string from [next_pos, occurance_of_delimiter)
	* Function: string extractToken
	* param   : constant string reference + size_t reference + bool reference
	* return  : a substring from str [next_pos, static delimiter)
	*
	* Condition: Words seperated by a delimitier
	* Ex.
	* str      = "Hello | World";
	* next_pos = 0u; 
	* more     = true;
	* 
	* extractToken(str, next_pos, more) -> returns "Hello"
	* 
	*/
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		/*
		This function:
		* uses the delimiter to extract the next token from str starting at position next_pos.
		* If successful, return a copy of the extracted token found (without spaces at the beginning/end),
		* update next_pos with the position of the next token, and set more to true (false otherwise).
		* reports an exception if a delimiter is found at next_pos.
		* updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
		* Note: in this application, str represents a single line that has been read from an input file.
		*/

		if (str[next_pos] == this->m_delimiter)
		{
			more = false;
			throw std::invalid_argument("next_pos is at a delimiter...");
		}
		//Because +1 is added at the end of each next_pos -> no need to do +1 for other apperances
		std::string token{};
		
		//Assign the position + substring for the token
		auto position = str.find(this->m_delimiter, next_pos);
		if (position == std::string::npos)
		{
			more = false;
			position = str.find('\n');
			token = str.substr(next_pos, position - next_pos);
		}
		else
		{
			token = str.substr(next_pos, position - next_pos);
			more = true;
		}

		trim(token); // remove any whitespace from the front and end
		next_pos = position + 1; // start right after the delim // aka skip delim and be the char right after :D
		if (this->m_widthField < token.length())
			this->setFieldWidth(token.length());

		return token;
	}
}