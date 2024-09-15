#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	class Book
	{
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
		double getAvgPgPrChpt() const;
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);

		// TODO: In completing Part 1, add here the missing 
		// member prototypes that would be necessary for the 
		// Collection module code and tester module w3_p1.cpp 
		// to manage Book-type objects. 
		// 
		// In completing Part 2, add here the missing 
		// member prototypes that would be necessary for 
		// OrderedCollection module code and tester module 
		// w3_p2.cpp to manage Book-type object. 
		//
		// Write the implementations of these functions 
		// in Book.cpp file

		bool operator>(const Book& rhs) const;
		bool operator<(const Book& rhs) const;
		operator bool() const;

		//No resource so no need for rule of 5 no need for move or cpy


		std::ostream& print(std::ostream& os) const;

	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif