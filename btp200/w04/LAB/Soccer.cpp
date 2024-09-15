#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Soccer.h"
#include <cstring>
#include <iomanip>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 10, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	SoccerTeam::SoccerTeam() {
		this->setEmpty();
	}

	SoccerTeam::SoccerTeam(const char* tname, double fines, int foul) {
		this->setFine(fines, foul);
		this->setName(tname);
	}

	void SoccerTeam::setTeam(const SoccerTeam& team) {
		this->setName(team.m_teamName);
		this->setFine(team.m_fines, team.m_noFouls);
	}

	void SoccerTeam::setName(const char* tname) {
		strcpy(this->m_teamName, tname);
		if (isEmpty())
			strcpy(this->m_teamName, tname);
		else {
			setEmpty();
		}
	}

	void SoccerTeam::setFine(double fines, int foul) {
		if (fines >= 0 && foul >= 0) {
			this->m_fines = fines;
			this->m_noFouls = foul;
		}
		else {
			this->setEmpty();
		}
	}

	void SoccerTeam::setEmpty() {
		this->m_teamName[0] = '\0';
		this->m_fines = -1;
		this->m_golas = 0;
		this->m_noFouls = -1;
	}

	bool SoccerTeam::isEmpty() const {
		if (this->m_teamName[0] == '\0' || (this->m_fines < 0 && this->m_noFouls < 0))
			return false;
		return true;
	}

	void SoccerTeam::calFines() {
		this->m_fines = (this->m_fines * 0.2) + this->m_fines;
	}

	int SoccerTeam::fouls() const {
		return this->m_noFouls;
	}

	std::ostream& SoccerTeam::display()const {
		if (isEmpty() &&  this->fouls() >= 0) {
			cout.width(30);
			cout.fill(' ');
			cout << std::left << this->m_teamName;
			cout.unsetf(ios::left);
			cout.width(6);
			cout << fixed << setprecision(2) << this->m_fines;
			cout.width(6);
			cout << this->m_noFouls;
			cout.width(10);
			if (m_golas > 0)
				cout << this->m_golas << "w";
			else {
				cout << this->m_golas;
				cout << " ";
			}
		}
		else {
			cout << "Invalid Team";
		}
		return cout;
	}
}