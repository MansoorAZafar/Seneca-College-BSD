#ifndef SDDS_SOCCER_H
#define SDDS_SOCCER_H
#include <iostream>
const int MAX_FOUL = 4;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {


	struct SoccerTeam {
		char m_teamName[41] = {};// a statically allocated Cstring with size 41. Remember, name could be 
		//maximum 40 characters long and 1 byte is for the null byte.
		int m_noFouls = -1;//number of fouls, it can be zero or more but cannot be a negative number
		double m_fines = -1;//it can be equal to and more than zero.
		int m_golas = 0;//can be zero or more
	public:
		void setTeam(const SoccerTeam& team);
		void setName(const char* tname);
		void setFine(double fines, int foul);
		void setEmpty();
		bool isEmpty() const;
		void calFines();
		int fouls() const;
		SoccerTeam();
		SoccerTeam(const char* tname, double fines, int foul);
		std::ostream& display()const;
	};
}
#endif