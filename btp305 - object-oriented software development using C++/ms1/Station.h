#ifndef SDDS_STATION_H
#define SDDS_STATION_H

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
		Station() = default;
		Station(const std::string& record);
		//-------------------------------------

		//ACCESSOR/QUERIES
		const std::string& getItemName() const;
		size_t getQuantity() const;
		void display(std::ostream& cout, bool full) const;
		//-------------------------------------

		//Mixed : Gets & Sets
		size_t getNextSerialNumber();
		//-------------------------------------

		//MUTATORS/MODIFERS
		void updateQuantity();
		//-------------------------------------
	};
}

#endif