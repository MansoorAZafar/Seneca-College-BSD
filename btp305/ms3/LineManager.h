#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include <iostream>
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
	class LineManager
	{
	private:

		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:

		// This function populates the m_activeLane vector with data from a file
		LineManager(const std::string& file, const std::vector<Workstation*>& station);
		
		// This function sorts the m_activeLane vector based on connections of the stations
		void reorderStations();

		//
		bool run(std::ostream& os);
		
		// This function displays the contents of the m_activeLane
		void display(std::ostream& os) const;
	};
}

#endif