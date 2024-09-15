#include <iomanip>
#include <string>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-11-17
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

//Edited on : 2023-11-28 : added comments + modified fillItem & isItemFilled


namespace sdds
{
	//Initalize Class Member
	size_t CustomerOrder::m_widthField{ 0 };

	//Constructors
	//Extracts the tokens from the string and populates the current instance
	//The fields in the string are (separated by a delimiter stored in Utilities module):
	//	1. Customer Name
	//	2. Order Name
	//	3. the list of items making up the order(at least one item)
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util;
		//------------------------
		//Count number of items:
		size_t cntItems{};
		auto next_pos = str.find(util.getDelimiter());
		while (next_pos != std::string::npos)
		{
			++cntItems;
			next_pos = str.find(util.getDelimiter(), next_pos + 1);
		}
		++cntItems; // to account for the first item
		cntItems -= 2; // remove the Customer Name & Order Name
		//------------------------

		size_t endPosition{};
		next_pos = 0u;
		auto trim = [](std::string& str)
			{
				auto start = str.find_first_not_of(" ");
				auto end = str.find_last_not_of(" ");
				str = str.substr(start, end - start + 1);
			};
		//------------------------

		auto getProperty = [&]() -> std::string
			{
				std::string property{};
				endPosition = str.find(util.getDelimiter(), next_pos);
				if (endPosition == std::string::npos)
					endPosition = str.find('\n');

				property = str.substr(next_pos, endPosition - next_pos);
				trim(property);
				next_pos = endPosition + 1;
				return property;
			};
		//------------------------

		//Customer Name -> Order Name -> list of items (atleast one item)
		this->m_name = std::move(getProperty());
		this->m_product = std::move(getProperty());
		//------------------------
		this->m_listItem = new Item * [cntItems];
		while (this->m_cntItem < cntItems)
		{
			*(this->m_listItem + this->m_cntItem) = new Item(getProperty());
			++this->m_cntItem;
		}
		this->m_widthField = this->m_widthField > this->m_product.length() ? this->m_widthField : this->m_product.length();

	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other)
	{
		throw std::logic_error("Cannot copy the CustomerOrder class");
	}

	//Move Operations
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this == &other)
			return *this;

		//cleanup! cleanup! everybody, everybody cleanup!
		if (this->m_listItem != nullptr)
		{
			for (auto i = 0u; i < this->m_cntItem; ++i)
				delete (*(this->m_listItem + i));
			delete[] this->m_listItem;
		}

		this->m_name = std::move(other.m_name);
		this->m_product = std::move(other.m_product);
		this->m_cntItem = other.m_cntItem;
		this->m_listItem = other.m_listItem;

		//'delete' the 'other' properties
		other.m_listItem = nullptr;
		other.m_cntItem = 0u;

		return *this;
	}

	//Destructor
	CustomerOrder::~CustomerOrder()
	{
		if (this->m_listItem != nullptr)
		{
			for (auto i = 0u; i < this->m_cntItem; ++i)
				delete (*(this->m_listItem + i));
			delete[] this->m_listItem;
		}
	}

	//returns true if all the items in the order have been filled; false otherwise
	bool CustomerOrder::isOrderFilled() const
	{
		for (auto i = 0u; i < this->m_cntItem; ++i)
			if (!((*(this->m_listItem + i))->m_isFilled)) // equivilent to if(this->m_listItem[i]->m_isFilled == false)
				return false;
		return true;
	}

	// Returns true if all items specified by itemName have been filled.
	// If the item doesn't exist in the order, this query returns true.
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool flag{true};
		for (size_t i = 0u; i < this->m_cntItem; ++i)
		{
			if ((*(this->m_listItem + i))->m_itemName == itemName)
				flag = (*(this->m_listItem + i))->m_isFilled;
		}
		return flag;
	}


	//This modifier fills one item in the current order that the Station specified
	//If item is found and the quantity is > 0 -> Then it is filled
	//bro
	//This one took me so long CUS IT DIDNT WORK PROPERLY WITH WORKSTATION 
	//ALL CUS ASADHsudsaidsidahsdhasdhasjdha
	//AHHHH
	//I JUST DIDNT LOOP IT CUS I WANTED TO BE FANCY
	//BRUHHHH
	void CustomerOrder::fillItem(Station& station, std::ostream& ostr)
	{	
		bool found{ false };
		size_t index{};
		for (size_t i = 0u; i < this->m_cntItem; ++i)
		{
			if ((*(this->m_listItem + i))->m_itemName == station.getItemName() && (*(this->m_listItem + i))->m_isFilled == false && !found)
			{
				index = i;
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					(*(this->m_listItem + index))->m_isFilled = true;
					(*(this->m_listItem + index))->m_serialNumber = station.getNextSerialNumber();
					ostr << "    Filled " << this->m_name <<
						", " << this->m_product << " [" << (*(this->m_listItem + index))->m_itemName << "]\n";
					found = true;
				}
				else
				{
					ostr << "    Unable to fill " << this->m_name << ", " << this->m_product
						<< " [" << (*(this->m_listItem + index))->m_itemName << "]\n";
				}
			}
		}
	}


	void CustomerOrder::display(std::ostream& ostr) const
	{
		ostr << this->m_name << " - " << this->m_product << "\n";
		for (auto i = 0u; i < this->m_cntItem; ++i)
		{
			std::string_view status = this->isItemFilled((*(this->m_listItem + i))->m_itemName) ? "FILLED" : "TO BE FILLED";
			ostr << "[" << std::setw(6) << std::setfill('0') << std::right << (*(this->m_listItem + i))->m_serialNumber << std::left << std::setfill(' ') << "] "
				<< std::setw(this->m_widthField) << std::left << (*(this->m_listItem + i))->m_itemName <<
				" - " << status << "\n";
		}
	}
}