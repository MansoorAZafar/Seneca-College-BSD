#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <string>
#include <cstring>
#include "RideRequest.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


double g_taxrate = 0;
double g_discount = 0;

sdds::RideRequest::RideRequest()
{
	this->setEmpty();
}

std::istream& sdds::RideRequest::read(std::istream& istr)
{
	if (istr)
	{
		if (this->m_description != nullptr)
		{
			delete[] this->m_description;
		}

		//Initalize Temp Variables
		char discount{};
		char name[10]{};
		std::string desc{}; // USED FOR READING ONLY
		double price{};

		//Store the results on the temp variables
		istr.getline(name, 10, ',');
		std::getline(istr, desc, ',');
		istr >> price;
		istr.ignore();
		istr >> discount;

		std::strcpy(this->m_customerName, name);

		
		this->m_description = new char[desc.length() + 1];
		std::strcpy(this->m_description, desc.c_str());

		this->m_discount = discount == 'Y' ? true : false;
		
		this->m_price = price;
	}
	return istr;
}

std::ostream& sdds::RideRequest::display(std::ostream& ostr) const
{
	static int funcCall = 1;
	auto baseWidth = ostr.width(2);
	ostr << std::left << funcCall << ". " << std::setw(10);
	++funcCall; // increase counter for each time this function is called
	if (this->m_customerName[0] == '\0')
	{
		ostr << "No Ride Request\n";
		return ostr;
	}
	//If the name is not empty:
	double price = (this->m_price * g_taxrate) + this->m_price;
	ostr << this->m_customerName << "|" << std::setw(25) << this->m_description <<
		"|" << std::setw(12) << std::fixed << std::setprecision(2)
		<< price << "|";
	this->m_discount == 1 ? ostr << std::setw(13) << std::right << (price - g_discount) : ostr << std::setw(0) << "";
	ostr << "\n";
	ostr << std::setw(baseWidth);
	return ostr;
}

sdds::RideRequest::~RideRequest()
{
	if (this->m_description != nullptr)
	{
		delete[] this->m_description;
	}
}

void sdds::RideRequest::setEmpty()
{
	this->m_customerName[0] = '\0';
	this->m_description = nullptr;
	this->m_price = 0;
	this->m_discount = false;
}

sdds::RideRequest& sdds::RideRequest::operator=(const RideRequest& rhs)
{
	if (this != &rhs)
	{
		delete[] this->m_description;
		this->setEmpty();
		if (rhs.m_description != nullptr)
		{
			std::strcpy(this->m_customerName, rhs.m_customerName);

			this->m_description = new char[strlen(rhs.m_description) + 1];
			std::strcpy(this->m_description, rhs.m_description);

			this->m_discount = rhs.m_discount;
			this->m_price = rhs.m_price;
		}
	}
	return *this;
}

sdds::RideRequest::RideRequest(const RideRequest& rhs)
{
	*this = rhs;
}