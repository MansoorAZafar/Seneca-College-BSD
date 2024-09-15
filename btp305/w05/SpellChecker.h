#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	class SpellChecker
	{
		std::string m_badwords[6]{};
		std::string m_goodwords[6]{};
		size_t m_replacements[6]{};

	public:
		
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& ostr) const;		
	};
}

#endif