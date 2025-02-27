#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"

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

	/*
	* 1. 3 double ended queues
	* 2. hold orders at either ends of the assembly line
	* 3.- pending	: orders to be placed
	*	- completed	: removed from last station + completely filled
	*	- incomplete: removed from last station + not filled
	* 4. All deque's should be accessible outside this module
	*/

	//To avoid redefinition 
	// This module is included in LineManager
	// externs -> defined in "Workstation.cpp" with empty initalizer list "{}"
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	//is-a-kind-of relation (inheritance) Station
	//Represents a single locatioon
	//Defines an active 'station'
	class Workstation : public Station
	{
	private:

		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};

	public:

		// Default constructor
		Workstation() = default;

		// This constructor calls the 'Station' constructor with the given string
		Workstation(const std::string& str);

		// This function attempts to call the CustomerOrder::fillItem function on the front of the m_orders attribute as long as m_orders isn't empty
		void fill(std::ostream& os);

		// This function will attempt to move the front value from m_orders into either (global) g_completed, g_incomplete, (member) m_pNextStation attributes
		bool attemptToMoveOrder();

		// This function assigns the m_pNextStation member to the parameter station 
		void setNextStation(Workstation* station = nullptr);

		// This function returns the m_pNextStation member
		Workstation* getNextStation() const;

		// This function displays the current objects Station::ItemName and the m_pNextStation
		void display(std::ostream& os) const;

		// This operator calls the move operations on the newOrder to be inserted into the m_orders member
		Workstation& operator+=(CustomerOrder&& newOrder);

		// Remove Copy and Move Operations
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

	};
}

#endif