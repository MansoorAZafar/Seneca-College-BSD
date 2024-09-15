#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream> //uses std::ostream
#include <string> // uses std::string
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

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
	private:

		//Instance Variables
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_listItem{};

		static size_t m_widthField;

	public:
		//Constructors
		CustomerOrder() = default;
		CustomerOrder(const std::string& token);

		//Copy Constructor + Assignment
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;

		//Move Constructor + Assignment
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;

		//Destructor
		~CustomerOrder();

		//Queries
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void display(std::ostream& cout) const;

		//Modifiers
		void fillItem(Station& station, std::ostream& cout);

	};

}

#endif