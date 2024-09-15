#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

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
	/* This function populates the m_activeLane vector with data from a file
	* 
	* Function: Constructor LineManager
	* param   : a filename and a vector of active 'stations'
	* return  : n/a
	*/ 
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& station)
	{
		std::ifstream AssemblyLine(file);

		if (AssemblyLine.fail()) 
			throw std::logic_error(file + " does not exist...");  // If there is an issue with the file
		

		Utilities util{};
		bool      more{true};
		size_t    next_pos{ 0u };

		std::string  line{}; // a string to hold each line of the file
		Workstation* root{};
		Workstation* current{};
		//Reads entire file --> x lines 
		while (AssemblyLine)
		{
			std::getline(AssemblyLine, line);
			if (AssemblyLine)
			{
				/*
				* Assumption:
				* line will ALWAYS have [1,2] items per line,
				* -------------
				* 
				* Problem: 
				* -> Need to put items per line into the Workstation* vector m_activeLine,
				* -------------
				* 
				* The Solution:
				* -------------
				* -> Extract the rootStation name (as a string)
				* -> Check if theres more 
				* -> If yes: 
				*		   -> Get the currentStation name (as a string) 
				* -> If no:
				*		   -> move onto next step
				* 
				* -> define a lambda to find it's corrosponding workstation*
				* -> Assign the root and current Workstation pointers
				* -> If the current Workstation is equal to .end() assign it to nullptr
				* -> Assign the root's next Workstation to the current 
				* -> push back the root into the activeLine
				* -> Incremenet the customer Count
				*/
				
				std::string rootStation = util.extractToken(line, next_pos, more), currentStation{};
				if (more)
					currentStation = util.extractToken(line,next_pos,more);
				
				
				auto getIterator = [&station](const std::string& stationName)
					{
						// Returns nullptr if doesn't exist...
						auto it = std::find_if(station.begin(), station.end(), [&stationName](Workstation* workstation)
							{
								return workstation->getItemName() == stationName;
							});
						return it == station.end() ? nullptr : *it;
					};
				
				root    = getIterator(rootStation);
				current = getIterator(currentStation);

				root->setNextStation(current);
				this->m_activeLine.push_back(root);
			}
		}
		this->m_firstStation = this->m_activeLine[0];
		this->m_cntCustomerOrder = g_pending.size();
	}


	/* This function sorts the m_activeLane vector based on connections of the stations
	*
	* Function: void reorderStations
	* param   : n/a
	* return  : n/a
	*/
	void LineManager::reorderStations()
	{
		//Get the first station
		std::vector<Workstation*> reOrder{this->m_activeLine};
		Workstation* currentOrder{};
		std::for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&reOrder, &currentOrder](Workstation* origin)
			{
				//Check if someone points to the origin
				//If someone does then the count > 0
				//Otherwise count == 0
				auto count = std::count_if(reOrder.begin(), reOrder.end(), [&origin](const Workstation* current)
					{
						return (origin == current->getNextStation());
					});
				if (!count)
					currentOrder = origin;
			});
		this->m_firstStation = currentOrder;
		
		/*
		* ~ notes
		* --------------
		* The order I want in the end is 
		* Bed -> Desser -> Armchair -> Nighttable -> Desk -> Office Chair -> Filing Cabnit -> Bookcase
		* I know the next value will be the ->getNextStation()
		*/
		//Reorder activeLane


		int index{0};
		while (currentOrder != nullptr)
		{			
			*(reOrder.begin() + index) = currentOrder;            //Same as reOrder[index] = currentOrder;
			currentOrder = currentOrder->getNextStation(); // move the order along the line
			++index;
		}
		this->m_activeLine = std::move(reOrder);

	}


	/* This function sorts the m_activeLane vector based on connections of the stations
	*
	* Function: void reorderStations
	* param   : n/a
	* return  : n/a
	*/
	bool LineManager::run(std::ostream& os)
	{
		/*
		* Init a variable to store how many times the functions been called (local static var)
		* ouput it to stream with 'os' in the format: Line Manager Iteration: COUNT<endl>
		* Move the order from the front of g_pending into the first_station
		* Remove it from the queue
		* Moves only 1 order to the line per call
		* FOr each station on the line -> call the respective fill
		* Attempt to move an order down the line
		* return true if all customer orders have or cannot be filled so gcomplete + gincomplete 
		* otherwise return false;
		*/

		static unsigned int functionCalls{ 0u };
		os << "Line Manager Iteration: " << ++functionCalls << "\n";

		if(!g_pending.empty())
		{
			this->m_firstStation->operator+=(std::move(g_pending.front()));
			g_pending.pop_front();
		}

		//Going station to station
		std::for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&os](Workstation* current)
			{
				current->fill(os); //filling it
			});

		std::for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&os](Workstation* current)
			{
				current->attemptToMoveOrder();
			});

		return this->m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
		
	}

	/* This function displays the contents of the m_activeLane
	*
	* Function: void display
	* param   : n/a
	* return  : n/a
	*/
	void LineManager::display(std::ostream& os) const
	{
		std::for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&os](const Workstation* current)
			{
				current->display(os);
			});
	}
}