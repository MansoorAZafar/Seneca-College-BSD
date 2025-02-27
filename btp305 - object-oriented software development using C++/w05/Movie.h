#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <iostream>
#include <string>
#include "SpellChecker.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	class Movie {

		std::string m_title{};
		size_t m_year{};
		std::string m_desc{};

	public:

		Movie();
		const std::string& title() const;
		Movie(const std::string& strMovie);
		
		template <class T>
		void fixSpelling(T& spellChecker);
		
		friend std::ostream& operator<<(std::ostream& ostr, const Movie& movie);
	};

	template <class T>
	void Movie::fixSpelling(T& spellChecker)
	{
		std::string text = this->m_title + ", "
			+ std::to_string(this->m_year) + ", "
			+ this->m_desc;

		spellChecker(text);

		*this = Movie(text);

	}

}

#endif