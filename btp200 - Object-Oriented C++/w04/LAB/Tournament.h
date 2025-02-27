#ifndef SDDS_TOURNAMENT_H
#define SDDS_TOURNAMENT_H
#include <iostream>
#include "Soccer.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {


	class Tournament {
		char* m_name = nullptr;//points to a dynamically allocated Cstring
		int m_num = 0;//size of the dynamically allocated array of soccer team. It should be more then zero.
		SoccerTeam* m_soccer = nullptr;//pointer to the dynamically allocated array of soccerTeam

	public:
		void setTournament(const char* name, int noOfteam, const SoccerTeam* soccer);
		void setEmpty();
		bool isEmpty() const;
		Tournament& match(const SoccerTeam* ls); // I removed the const
		ostream& display() const;
		Tournament();
		Tournament(const char* name, int noOfteam, const SoccerTeam* soccer);
		~Tournament();
	};


}
#endif