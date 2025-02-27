#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <iostream>
#include <string>
#include "SpellChecker.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	class Book
	{
	private:
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{};
		double m_price{};
		std::string m_desc{};
	public:

		//Query Functions
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();

		//Constructor
		Book();
		
		Book(const std::string& strBook);

		//Mutator
		void setPrice(const double& price);

		template <class T>
		void fixSpelling(T& spellChecker);
		
		Book(const Book& book);
		Book& operator=(const Book& book);
		/*Book(Book&& book);
		Book& operator=(Book&& book);*/

		friend std::ostream& operator<<(std::ostream& ostr, const Book& book);
	};

	template<class T>
	void Book::fixSpelling(T& spellChecker)
	{
		spellChecker(this->m_desc);

	}

}

#endif