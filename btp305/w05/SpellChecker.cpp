#include <iomanip>
#include <fstream>
#include <string>
#include "SpellChecker.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	SpellChecker::SpellChecker(const char* filename)
	{
		std::ifstream ifstr(filename);
		if (!ifstr)
		{
			throw "Bad file name!";
		}
		size_t cnt{};
		std::string bad{}, good{};
		do
		{
			ifstr >> bad >> good;
			if (ifstr)
			{
				this->m_badwords[cnt] = bad;
				this->m_goodwords[cnt] = good;
				++cnt;
			}
		} while (ifstr);

		//Could do this concept in the while loop if you wanted...
		/*
		auto a = line.find_first_not_of(" ");
		auto b = line.find_first_of(" ", a+1);
		std::cout << line.substr(a, b-a + 1) << std::endl;
		line.erase(a, b + 1);
		//----------------------
		a = line.find_first_not_of(" ");
		b = line.find_first_of("\n");
		std::cout << line.substr(a, b - a + 1) << std::endl;
		line.erase(a, b + 1);
		*/
	}

	void SpellChecker::operator()(std::string& text)
	{
		size_t index = 0u;
		while (index < 6)
		{
			auto position = text.find(this->m_badwords[index]);
			if (position == std::string::npos)
			{
				++index;
			}
			else
			{
				text.replace(position, this->m_badwords[index].length(), this->m_goodwords[index]);
				++this->m_replacements[index];
			}
		}

	}

	void SpellChecker::showStatistics(std::ostream& ostr) const
	{
		ostr << "Spellchecker Statistics\n";
		for (auto i = 0u; i < 6u; ++i)
		{
			ostr << std::right << std::setw(15) << this->m_badwords[i]
				<< ": " << this->m_replacements[i] << " replacements" << "\n";
		}
	}
}