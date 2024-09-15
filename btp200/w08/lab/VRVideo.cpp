// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | March 22, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include "VRVideo.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace sdds {

	VRVideo::VRVideo() : Video()
	{
		this->m_equipment = nullptr;
	}

	VRVideo::VRVideo(const int length, const char* name) : Video(length)
	{
		//make sure length is valid since it shouldn't work if either of the two fail
		if (this->get() > 0 && name != nullptr) {
			this->m_equipment = new char[strlen(name) + 1];
			strcpy(this->m_equipment, name);
		}
		else {
			this->setEmpty();
			this->m_equipment = nullptr;
		}
	}

	VRVideo::~VRVideo()
	{
		delete[] this->m_equipment;
	}

	void VRVideo::load(std::istream& istr)
	{
		delete[] this->m_equipment;
		this->m_equipment = nullptr;
		Video::load(istr);
		char buffer[5]; //obsolete buffer size just a size for the buffer to read at a time
		auto size = 0;
		bool flag = true;
		while (flag) {
			istr >> setw(5);
			istr.get(buffer, 5, '\n');
			if (istr) {
				char* tmp = new char[size + strlen(buffer) + 1];
				if (this->m_equipment) {
					strcpy(tmp, this->m_equipment);
					strcat(tmp, buffer);
				}
				else {
					strcpy(tmp, buffer);
				}
				delete[] this->m_equipment;
				this->m_equipment = tmp;
				size += strlen(buffer);
				if (strlen(buffer) < 4) {
					flag = false;
					cin.clear();
					cin.ignore();
				}
			}
		}		
	}

	ostream& VRVideo::play(std::ostream& ostr) const
	{
		if (this->get() > 0 && this->m_equipment != nullptr) {
			ostr << "VRVideo requires " << this->m_equipment << endl
				<< "Video Length = " << this->get();
		}
		return ostr;
	}
}