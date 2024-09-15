#include "Cheese.h"
#include <iostream>
#include <iomanip>
#include <string>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	Cheese::Cheese()
	{}

	Cheese::Cheese(const std::string& strs)
	{
		std::string str = strs;
		size_t cnt{};
		auto position = str.find_first_of(",");
		while (position != std::string::npos)
		{
			++cnt; // count # of ,
			position = str.find(",", position+1);
		}

		++cnt; // # of commas + 1 = how many items is on a line

		std::string* properties = new std::string[cnt]; 
		for (auto i = 0u; i < cnt; ++i)
		{

			position = str.find_first_of(",");
			if (position == std::string::npos)
				position = str.find_first_of("\n");
			properties[i] = str.substr(0, position);
			str.erase(0, position + 1);
			
			position = properties[i].find_first_not_of(" "); // finds the first char index
			auto posEnd = properties[i].find_last_not_of(" "); // finds the last character index
			properties[i] = properties[i].substr(position, posEnd-position+1); 
			//logic: Take the substring from the first to the last character
			//reason why it's not position, endPosition -> it takes position as '0' in a sense
			// meaning it'll take 0 -> endPos but endPos is only respective to position not being 0 but it's original value from ln 39
			// unless it's originally 0 it'll give bad answer; -> we add 1 since substrings start from 0 meaning it'll take off one
			// if I don't add the 1 extra
		}

		this->m_name = properties[0];
		this->m_weight = std::stoul(properties[1]);
		this->m_price = std::stod(properties[2]);
		for (auto i = 3u; i < cnt; ++i)
		{
			this->m_features += properties[i] + " ";
		}
		delete[] properties;
	}

	Cheese Cheese::slice(const size_t& weight)
	{
		if (weight <= this->m_weight)
		{
			this->m_weight -= weight;
			Cheese tmp = Cheese(*this);
			tmp.m_weight = weight;
			return tmp;
		}
		return Cheese();
	}
	std::string Cheese::getName() const
	{
		return this->m_name;
	}

	size_t Cheese::getWeight() const
	{
		return this->m_weight;
	}

	double Cheese::getPrice() const
	{
		return this->m_price;
	}

	std::string Cheese::getFeatures() const
	{
		return this->m_features;
	}

	Cheese::Cheese(const Cheese& rhs)
	{
		*this = rhs;
	}

	Cheese& Cheese::operator=(const Cheese& rhs)
	{
		if (this != &rhs)
		{
			this->m_features = rhs.m_features;
			this->m_name = rhs.m_name;
			this->m_price = rhs.m_price;
			this->m_weight = rhs.m_weight;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const Cheese& cheese)
	{
		ostr << "|" << std::left << std::setw(21) << cheese.getName() <<
			"|" << std::setw(5) << cheese.getWeight() <<
			"|" << std::fixed << std::setprecision(2) << std::setw(5) << cheese.getPrice() <<
			"|" << std::right << std::setw(34) << cheese.getFeatures() <<
			"|\n";
		return ostr;
	}
}