#include <iomanip>
#include <fstream>
#include <string>
#include "AirportModels.h"


// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 23, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

std::ostream& sdds::operator<<(std::ostream& ostr, const sdds::Airport rhs)
{
	if (!rhs.m_name.empty())
	{
		ostr << std::right << std::setw(20) << std::setfill('.')
			<< "Airport Code" << " : " << std::left << std::setw(30) << rhs.m_code << "\n"
			<< std::right << std::setw(20) << 
			"Airport Name" << " : " << std::left << std::setw(30) << rhs.m_name
			<< "\n" << std::right << std::setw(20) 
			<< "Airport City" << " : " <<
			std::left << std::setw(30) << rhs.m_city << "\n" << std::right << std::setw(20)
			<< "Airport State" << " : " << std::left << std::setw(30) <<
			rhs.m_state << "\n" << std::right << std::setw(20) <<
			"Airport Country" << " : " << std::left << std::setw(30) <<
			rhs.m_country << "\n" << std::right << std::setw(20) 
			<< "nAirport Latitude" <<
			" : " << std::left << std::setw(30) << rhs.m_latitude << "\n" << 
			std::right << std::setw(20) 
			<< "Airport Longitude" << " : " << std::left << std::setw(30) 
			<< rhs.m_longitude;
		return ostr << std::setw(0) << "\n";
	}
	return ostr << "Empty Airport";
}

sdds::AirportLog::AirportLog() : m_AirportPtr{ nullptr }, m_count{ 0 }
{}

sdds::AirportLog::AirportLog(const char* filename) // DONE
{
	//Step 1: read the file to count the number of airports
	std::ifstream ifstr(filename);
	std::string line{}; // to hold the info
	//Reading the lines
	while (!ifstr.eof())
	{
		std::getline(ifstr, line, '\n');
		++this->m_count;
	}
	//this->m_count = 322;

	//Step 2: heading line in the file is not counted so -1
	--this->m_count;
	//Step 3: allocate dynamic memory for the array of airports based on the number found
	this->m_AirportPtr = new Airport[this->m_count];

	//Step 3.5: Reopen file / set pos to 0:
	ifstr.clear();
	ifstr.seekg(0);

	//Step 4: add data from file into array
	//Temporary values to hold information
	int index = -1;
	std::string iata_code{};
	std::string airport{};
	std::string city{};
	std::string state{};
	std::string country{};
	double latitude{};
	double longitude{};
	while (!ifstr.eof())
	{
		if (index < 0)
		{
			//Skip : this line is the heading line
			std::getline(ifstr, line, '\n');
		}
		else
		{
			std::getline(ifstr, iata_code, ',');
			std::getline(ifstr, airport, ',');
			std::getline(ifstr, city, ',');
			std::getline(ifstr, state, ',');
			std::getline(ifstr, country, ',');
			ifstr >> latitude;
			ifstr.ignore();
			ifstr >> longitude;
			this->m_AirportPtr[index].m_code = iata_code;
			this->m_AirportPtr[index].m_name = airport;
			this->m_AirportPtr[index].m_city = city;
			this->m_AirportPtr[index].m_state = state;
			this->m_AirportPtr[index].m_country = country;
			this->m_AirportPtr[index].m_latitude = latitude;
			this->m_AirportPtr[index].m_longitude = longitude;
			
		}
		++index;
	}
}

void sdds::AirportLog::addAirport(const sdds::Airport& other)
{
	//Create a temporary place to store old data
	sdds::Airport* temporary = new sdds::Airport[this->m_count + 1];

	//Move old data into temporary
	for (size_t i = 0; i < this->m_count; ++i)
	{
		temporary[i] = this->m_AirportPtr[i];
	}

	//delete arr
	delete[] this->m_AirportPtr;

	//Add new data / other to temporary
	temporary[this->m_count] = other;

	//Set pointer to temporary
	this->m_AirportPtr = temporary;

	//increment m_count
	++this->m_count;
}

sdds::AirportLog sdds::AirportLog::findAirport(const char* state, const char* country) const // DONE
{
	//Step 1: Count number of airports with X state and X country
	int count = 0;
	{
		for (size_t i = 0; i < this->m_count; ++i)
		{
			if (this->m_AirportPtr[i].m_state == state && this->m_AirportPtr[i].m_country == country)
			{
				++count;
			}
		}
	}

	//Step 2: Create a new AirportLog object to be returned
	sdds::AirportLog tmp;
	tmp.m_count = count;

	//Allocate the array:
	tmp.m_AirportPtr = new sdds::Airport[tmp.m_count + 1];
	int index = 0;
	//Set the values
	{
		for (size_t i = 0; i < this->m_count; ++i)
		{
			if (this->m_AirportPtr[i].m_state == state && this->m_AirportPtr[i].m_country == country)
			{
				tmp.m_AirportPtr[index] = this->m_AirportPtr[i];
				++index;
			}
		}
	}

	return tmp;
}

sdds::Airport sdds::AirportLog::operator[](size_t index) const
{
	if (index < this->m_count && index >= 0)
	{
		return this->m_AirportPtr[index];
	}
	return Airport();
}

sdds::AirportLog::operator size_t() const
{
	return this->m_count;
}

sdds::AirportLog::~AirportLog()
{
	delete[] this->m_AirportPtr;
}