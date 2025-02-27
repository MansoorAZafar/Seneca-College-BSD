#include <iomanip>
#include <string>
#include "Book.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	//=========================================================================================================
	//======== CONSTRUCTORS + DESTRUCTOR ========//
	//=========================================================================================================


	Book::Book()
		: m_title{}, m_numChapters{ 0 }, m_numPages{ 0 }
	{}


	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
		: m_title(title), m_numChapters(nChapters), m_numPages(nPages)
	{}

	//=========================================================================================================
	//======== END OF CONSTRUCTORS + DESTRUCTOR ========//
	//=========================================================================================================
	//======== PRINTING/OSTREAM ========//
	//=========================================================================================================


	std::ostream& sdds::Book::print(std::ostream& os) const
	{
		//Check if book is valid: {title has atleast: 1 char, 1 chpter and 1 page}
		if (*this)
		{
			//Combining all 3 title + chapters + pages into one string to have them all aligned in the width:
			const std::string bookInfo = this->m_title + "," + std::to_string(this->m_numChapters) + "," + std::to_string(this->m_numPages);

			//Avg pages per chpter:
			std::string avgPagePerChpt = "(" + std::to_string(this->getAvgPgPrChpt()) + ")";
			//Printing Info 
			os << std::right << std::setw(56) << bookInfo
				<< " | " << std::left << std::setw(15) << avgPagePerChpt;
		}
		else
		{
			os << "| Invalid book data";
		}
		return os;
	}


	std::ostream& operator<<(std::ostream& os, const Book& bk)
	{
		bk.print(os);
		return os;
	}


	//=========================================================================================================
	//======== END OF PRINTING/OSTREAM ========//
	//=========================================================================================================
	//======== BOOL OPERATORS ========//
	//=========================================================================================================


	bool Book::operator>(const Book& rhs) const
	{
		return this->getAvgPgPrChpt() > rhs.getAvgPgPrChpt();
	}

	bool Book::operator<(const Book& rhs) const
	{
		return  this->getAvgPgPrChpt() < rhs.getAvgPgPrChpt();
	}

	Book::operator bool() const
	{
		return this->m_title.length() > 0 && this->m_numPages > 0 && this->m_numChapters > 0;
	}


	//=========================================================================================================
	//======== END OF BOOL OPERATORS ========//
	//=========================================================================================================
	//======== ACCESSOR ========//
	//=========================================================================================================


	double Book::getAvgPgPrChpt() const
	{
		return this->m_numPages / double(this->m_numChapters);
	}


	//=========================================================================================================
	//======== END OF ACCESSOR ========//
	//=========================================================================================================
}