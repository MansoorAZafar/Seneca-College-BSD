#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"
#include "Station.h"

// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-11-17
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

//Edited on : 2023-11-28 : added comments

namespace sdds
{
	//Initalize Class Members
	size_t Station::m_widthField{ 0 };
	size_t Station::id_generator{ 0 };

	//-----------------------------------------
	// This string contains a single record (one line) that has been 
	// retrieved from the input file specified by the user.
	//
	// This constructor assumes that the string contains 
	// 4 fields separated by the delimiter, 
	// in the following order:
	//		1. name of the item
	//		2. starting serial number
	//		3. quantity in stock
	//		4. description
	//-----------------------------------------
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


	/* This function returns the m_itemName member 
	*
	* Function: string getItemName
	* param   : n/a
	* return  : The single item being managed by this station (class)
	*/
	const std::string& Station::getItemName() const
	{
		return this->m_itemName;
	}


	/* This function incremenets the m_serialNumber with postfix operation ++ and returns that value
	*
	* Function: size_t getNextSerialNumber
	* param   : n/a
	* return  : The serial number + 1 assigned to this single item on the station 
	*/
	size_t Station::getNextSerialNumber()
	{
		return this->m_serialNumber++;
	}


	/* This function returns the m_quantity member
	*
	* Function: size_t getQuantity
	* param   : n/a
	* return  : the quantity of a single item from this station
	*/
	size_t Station::getQuantity() const
	{
		return this->m_quantity;
	}


	/* This function decrements the m_quantity member with prefix operation --
	*
	* Function: void updateQuantity
	* param   : n/a
	* return  : n/a
	*/
	void Station::updateQuantity()
	{
		--this->m_quantity;
		if (this->m_quantity < 0u)
			this->m_quantity = 0u;
	}


	/* This function displays the Station's class contents
	*
	* Function: void display
	* param   : ostream reference + boolean
	* return  : n/a
	*/
	void Station::display(std::ostream& cout, bool full) const
	{
		if (full)
			cout << std::setfill('0') << std::setw(3) << std::right << this->m_stationID << std::left << std::setfill(' ') << " | " <<
			std::setw(this->m_widthField) << std::left << this->m_itemName << std::right << " | "
			<< std::setw(6) << std::setfill('0') << this->m_serialNumber << std::setfill(' ') << " | " <<
			std::setw(4) << this->m_quantity << " | " <<
			this->m_station_desc << "\n";
		else
			cout << std::setfill('0') << std::setw(3) << std::right << this->m_stationID << std::left << std::setfill(' ') << " | " <<
			std::setw(this->m_widthField) << std::left << this->m_itemName << std::right << " | " <<
			std::setw(6) << std::setfill('0') << this->m_serialNumber << std::setfill(' ') << " | " << "\n";
	}
}