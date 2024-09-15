#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
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
	class Station
	{
	private:
		size_t m_stationID{};
		std::string m_itemName{};
		std::string m_station_desc{};
		size_t m_serialNumber{};
		size_t m_quantity{};

		static size_t m_widthField;
		static size_t id_generator;

	public:
		//-------------------------------------
		//MANAGER/SPECIAL 
		// This function constructs 'this' with default values
		Station() = default;
		
		// This function populates the private properties with the 'record'
		Station(const std::string& record);
		//-------------------------------------

		//ACCESSOR/QUERIES
		// This function returns the m_itemName member 
		const std::string& getItemName() const;

		// This function returns the m_quantity member
		size_t getQuantity() const;

		// This function displays the Station's class contents
		void display(std::ostream& cout, bool full) const;
		//-------------------------------------

		//Mixed : Gets & Sets
		// This function incremenets the m_serialNumber with postfix operation ++ and returns that value
		size_t getNextSerialNumber();
		//-------------------------------------

		//MUTATORS/MODIFERS
		// This function decrements the m_quantity member with prefix operation --
		void updateQuantity();
		//-------------------------------------
	};
}

#endif