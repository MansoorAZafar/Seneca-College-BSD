//#include <iostream>
#include <string>
#include <iomanip>
#include "Movie.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	Movie::Movie()
	{}

	const std::string& Movie::title() const
	{
		return this->m_title;
	}

	Movie::Movie(const std::string& strMovie)
	{
		std::string str = strMovie;
		size_t cnt = 3; // number of properties per line for movies.txt
		//TITLE,YEAR,DESCRIPTION
		std::string properties[3]{};
		for (auto i = 0u; i < cnt; ++i)
		{
			auto position = str.find(",");
			if (i == cnt - 1)
				position = str.find("\n");

			properties[i] = str.substr(0, position);
			str.erase(0, position+1);

			position = properties[i].find_first_not_of(" ");
			if (position == std::string::npos)
				position = 0;
			auto endPosition = properties[i].find_last_not_of(" ");
			properties[i] = properties[i].substr(position, endPosition - position + 1);
		}
		/*
		Properties 0 - 2
		0: TITLE 
		1: YEAR
		2: DESCRIPTION
		*/
		this->m_title = std::move(properties[0]);
		this->m_year = std::stoi(properties[1]);
		this->m_desc = std::move(properties[2]);
	}

	std::ostream& operator<<(std::ostream& ostr, const Movie& movie)
	{
		ostr << std::setw(40) << movie.title() << " | "
			<< std::setw(4) << movie.m_year << " | "
			<< movie.m_desc;
		ostr << "\n";
		return ostr; 
	}
}