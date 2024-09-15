#include <iostream>
#include <deque>
#include <string>
#include "Workstation.h"

// Name: Mansoor Ahmad Zafar
// Seneca Student ID: 100503226
// Seneca email: mzafar15@myseneca.ca
// Date of completion: 2023-11-28
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& str) : Station(str)
	{}


	void Workstation::fill(std::ostream& os)
	{
		if (!this->m_orders.empty())
			this->m_orders.front().fillItem(*this, os);
	}

	// Conditions to return true:
	// The Stations quantity must be 0
	// OR
	// The front of the queue is filled
	bool Workstation::attemptToMoveOrder()
	{
		if (this->m_orders.empty())
			return false;

		//No more service means theres no items left or the item is filled
		// If the next station is empty and the order is filled
		// -> send it to g_completed
		// 
		// ELSE If the next station is empty and the order is NOT filled
		// -> send it to g_incomplete
		// 
		// ELSE If the next station is empty
		// -> add it to the next station
		// 
		// -> remove the front
		// return true

		if (this->getQuantity() == 0 || this->m_orders.front().isItemFilled(this->getItemName()))
		{
			if (this->m_pNextStation == nullptr && this->m_orders.front().isOrderFilled())
				g_completed.push_back(std::move(this->m_orders.front()));

			else if (this->m_pNextStation == nullptr)
				g_incomplete.push_back(std::move(this->m_orders.front()));
			
			else if (this->m_pNextStation != nullptr)
				this->m_pNextStation->operator+=(std::move(this->m_orders.front()));
			
			this->m_orders.pop_front();
			return true;
		}
		return false;
	}


	void Workstation::setNextStation(Workstation* station)
	{
		this->m_pNextStation = station;
	}
	

	Workstation* Workstation::getNextStation() const
	{
		return this->m_pNextStation;
	}


	void Workstation::display(std::ostream& ostr) const
	{
		ostr << this->getItemName() 
			<< " --> " 
			<< (this->m_pNextStation == nullptr ? "End of Line" : this->m_pNextStation->getItemName()) 
			<< "\n";
	}


	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		//moving an rval ref and customer order does not allow for cpy so have to do std::move
		this->m_orders.push_back(std::move(newOrder));
		return *this;
	}
}