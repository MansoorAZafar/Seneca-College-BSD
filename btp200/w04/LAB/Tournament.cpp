#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Tournament.h"
#include "Soccer.h"
#include <cstring>
#include <iomanip>
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	void Tournament::setTournament(const char* name, int noOfteam, const SoccerTeam* soccer) {
		//Makes it into this f(x)
		//cout << isEmpty();
		if (name != nullptr && noOfteam > 0) {

			SoccerTeam* tmp = new SoccerTeam[noOfteam];

			for (int i = 0; i < noOfteam; i++) {
				tmp[i] = soccer[i];
			}
			this->~Tournament();
			this->m_num = noOfteam;
			auto size = strlen(name) + 1;
			this->m_name = new char[size];
			strcpy(this->m_name, name);
			this->m_soccer = tmp;
		}
		else {
			setEmpty();
		}
	}

	void Tournament::setEmpty() {
		this->m_name = nullptr;
		//this->m_soccer = nullptr;
		this->m_num = 0;
	}

	bool Tournament::isEmpty() const {
		if (this->m_name != nullptr && this->m_num > 0) {
			return true;
		}
		return false;
	}

	//I removed the const
	Tournament& Tournament::match(const SoccerTeam* ls)
	{
		for (int i = 0; i < 1; i++) {
			if (m_soccer[i].fouls() < m_soccer[i + 1].fouls()) {
				m_soccer[i + 1].m_noFouls *= 2;
				m_soccer[i + 1].calFines();
				m_soccer[i].m_golas++;
				if (m_soccer[i + 1].m_noFouls > MAX_FOUL) {
					m_soccer[i + 1].m_noFouls = -1;
				}
			}
		}
		return *this;
	}

	ostream& Tournament::display() const {
		if (isEmpty()) {
			cout << "Tournament name: " << this->m_name << endl;
			cout << "list of the teams" << endl;
			cout.fill(' ');
			cout.width(40);
			cout << "";
			//cout.setf(ios::right);
			cout << "Fines";
			//cout.unsetf(ios::right);
			cout.width(10);
			cout.fill(' ');
			cout << "Fouls";
			cout.width(10);
			cout.fill(' ');
			cout << "Goals";
			//cout.width(2);
			//cout.fill('\0');
			cout << endl;
			for (int i = 0; i < this->m_num; i++) {
				cout << "Team[" << i + 1 << "] :";
				this->m_soccer[i].display() << endl;
			}
		}
		else {
			cout << "Invalid Tournament";
		}
		return cout;
	}

	Tournament::Tournament() {
		setEmpty();
		//Works
	}

	Tournament::Tournament(const char* name, int noOfteam, const SoccerTeam* soccer) {
		// Makes it into this f(x)
		this->setTournament(name, noOfteam, soccer);
	}

	Tournament::~Tournament() {
		delete[] this->m_name;
		m_name = nullptr;
		delete[] this->m_soccer;
		m_soccer = nullptr;
	}


}
