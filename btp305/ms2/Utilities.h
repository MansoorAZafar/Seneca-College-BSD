#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>

// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-11-17
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	class Utilities
	{
	private:
		//instance variable(s)
		size_t m_widthField{ 1 }; // default value is 1 
		//class variable(s)
		static char m_delimiter;  // delimiter for all class's
		void trim(std::string& str);

	public:

		//Mutator/Modifiers
		void setFieldWidth(size_t newWidth);
		static void setDelimiter(char newDelimiter);

		//Accessor/Queries
		size_t getFieldWidth() const;
		static char getDelimiter();

		//Manager/Special
		Utilities() = default;

		//Others
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more); //extracts a token from string str referred to by the first parameter.
	};
}

#endif