#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"
#include "Station.h"

// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-10-30
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	//Initalize Class Members
	size_t Station::m_widthField{ 0 };
	size_t Station::id_generator{ 0 };

	Station::Station(const std::string& record)
	{
		//increment and set ID & id_generator
		++Station::id_generator;
		this->m_stationID = this->id_generator;

		//Locally initalized Utilities for the delimitier
		Utilities util;

		//Order of Record:
		//name of the item -> starting serial number -> quantity in stock -> description
		size_t endPosition{};
		size_t next_pos{ 0u };

		auto trim = [](std::string& str)
			{
				//repeated multiple times so I made a lambda to do it
				auto position = str.find_first_not_of(" ");
				auto endPosition = str.find_last_not_of(" ");
				str = str.substr(position, endPosition - position + 1);
			};

		auto getProperty = [&]() -> std::string
			{
				std::string property{};
				endPosition = record.find(util.getDelimiter(), next_pos);
				if (endPosition == std::string::npos)
					endPosition = record.find('\n');
				property = record.substr(next_pos, endPosition - next_pos);
				trim(property);
				next_pos = endPosition + 1;
				return property;
			};

		this->m_itemName = std::move(getProperty());
		this->m_serialNumber = std::stoul(getProperty());
		this->m_quantity = std::stoul(getProperty());
		//Update m_widthField

		this->m_widthField = this->m_widthField > this->m_itemName.length() ? this->m_widthField : this->m_itemName.length();

		//Continue Extracting...
		this->m_station_desc = std::move(getProperty());
	}

	const std::string& Station::getItemName() const
	{
		return this->m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return this->m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return this->m_quantity;
	}

	void Station::updateQuantity()
	{
		--this->m_quantity;
		if (this->m_quantity < 0u)
			this->m_quantity = 0u;
	}

	void Station::display(std::ostream& cout, bool full) const
	{
		if (full)
			cout << std::setfill('0') << std::setw(3) << this->m_stationID << std::setfill(' ') << " | " <<
			std::setw(this->m_widthField) << std::left << this->m_itemName << std::right << " | " 
			<< std::setw(6) << std::setfill('0') << this->m_serialNumber << std::setfill(' ') << " | " <<
			std::setw(4) << this->m_quantity << " | " <<
			this->m_station_desc << "\n";
		else
			cout << std::setfill('0') << std::setw(3) << this->m_stationID << std::setfill(' ') << " | " <<
			std::setw(this->m_widthField) << std::left << this->m_itemName << std::right << " | " << 
			std::setw(6) << std::setfill('0') << this->m_serialNumber << std::setfill(' ') << " | " << "\n";
	}

}