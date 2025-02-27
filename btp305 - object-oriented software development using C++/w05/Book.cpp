#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iomanip>
#include "Book.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{

	//Queries
	const std::string& Book::title() const
	{
		return this->m_title;
	}

	const std::string& Book::country() const
	{
		return this->m_country;
	}

	const size_t& Book::year() const
	{
		return this->m_year;
	}

	double& Book::price()
	{
		return this->m_price;
	}

	//Constructor
	Book::Book(const std::string& strBook)
	{
		std::string str = strBook;
		size_t count{6u};// 6 categories in each book

		auto position = str.find(',');
		
		std::string properties[6]{};
		/*
		Properties: 0 -> 5
		0: author{};
		1: title{};
		2: country{};
		3: price{};
		4: year{};
		5: summary{};
		*/
		for (auto i = 0u; i < count; ++i)
		{
			//set the position
			position = str.find(",");
			if (i == count-1)
				position = str.find("\n");

			properties[i] = str.substr(0,position);
			str.erase(0,position+1);

			position = properties[i].find_first_not_of(" ");
			auto posEnd = properties[i].find_last_not_of(" ");
			properties[i] = properties[i].substr(position, posEnd - position + 1);
		}

		/*
		Properties: 0 -> 5
		0: author{};
		1: title{};
		2: country{};
		3: price{};
		4: year{};
		5: summary{};
		*/
		//Set the values
		this->m_author = std::move(properties[0]);
		this->m_title = std::move(properties[1]);
		this->m_country = std::move(properties[2]);
		this->m_price = std::stod(properties[3]);
		this->m_year = std::stoi(properties[4]);
		this->m_desc = std::move(properties[5]);
	}

	Book::Book()
	{}

	void Book::setPrice(const double& price)
	{
		this->m_price = price;
	}

	std::ostream& operator<<(std::ostream& ostr, const Book& book)
	{
		std::cout << std::setw(20) << book.m_author << " | "
			<< std::setw(22) << book.title() << " | "
			<< std::setw(5) << book.country() << " | " 
			<< std::setw(4) << book.year() << " | "
			<< std::setprecision(2) << std::fixed << std::setw(6) << book.m_price << " | " << book.m_desc << "\n";
		return ostr;
	}
	
	Book::Book(const Book& book)
	{
		*this = book;
	}

	Book& Book::operator=(const Book& book)
	{
		if (this == &book)
			return *this;

		this->m_author = book.m_author;
		this->m_country = book.m_country;
		this->m_desc = book.m_desc;
		this->m_price = book.m_price;
		this->m_title = book.m_title;
		this->m_year = book.m_year;
		
		return *this;
	}
}
