#include <iomanip>
#include <fstream>
#include <string>
#include "AirportModels.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 24, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


std::ostream& sdds::operator<<(std::ostream& ostr, const sdds::Airport& rhs)
{
	if (!rhs.m_name.empty())
	{
		ostr << std::right << std::setw(20) << std::setfill('.')
			<< "Airport Code" << " : " << std::left << std::setw(30) << rhs.m_code << "\n"
			<< std::right << std::setw(20) <<
			"Airport Name" << " : " << std::left << std::setw(30) << rhs.m_name
			<< "\n" << std::right << std::setw(20)
			<< "City" << " : " <<
			std::left << std::setw(30) << rhs.m_city << "\n" << std::right << std::setw(20)
			<< "State" << " : " << std::left << std::setw(30) <<
			rhs.m_state << "\n" << std::right << std::setw(20) <<
			"Country" << " : " << std::left << std::setw(30) <<
			rhs.m_country << "\n" << std::right << std::setw(20)
			<< "Latitude" <<
			" : " << std::left << std::setw(30) << rhs.m_latitude << "\n" <<
			std::right << std::setw(20)
			<< "Longitude" << " : " << std::left << std::setw(30)
			<< rhs.m_longitude;
			
		return ostr << "\n";
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
		this->m_count += (ifstr.get() == '\n');	
	}


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


	bool continueFlag = true;
	while (continueFlag)
	{
		if (ifstr)
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
				ifstr.ignore();

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
		if (ifstr.fail() || ifstr.peek() == EOF)
		{
			continueFlag = false;
		}
	}
	/*
	
	while (!ifstr.eof())
	{
		if (index < 0 || index >= this->m_count)
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
			ifstr.ignore();

			if (index >= 320) {
				std::cout << "[DEBUG :] INDEX: " << index << "\n"
					<< "[DEBUG] iata_code: " << iata_code << "\n"
					<< "[DEBUG] airport: " << airport << "\n\n";
			}


			this->m_AirportPtr[index].m_code = iata_code;
			this->m_AirportPtr[index].m_name = airport;
			this->m_AirportPtr[index].m_city = city;
			this->m_AirportPtr[index].m_state = state;
			this->m_AirportPtr[index].m_country = country;
			this->m_AirportPtr[index].m_latitude = latitude;
			this->m_AirportPtr[index].m_longitude = longitude;

			if (index >= 320) {
				std::cout << "[DEBUG : ] INDEX:" << index
					<< "\n[DEBUG] m.code: " << m_AirportPtr[index].m_code
					<< "\n[DEBUG] m.name: " << m_AirportPtr[index].m_name
					<< "\n------------------\n";
			}

		}
		++index;
	}
	
	*/
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
	if (index < this->m_count && index >= 0 && this->m_AirportPtr != nullptr)
	{
		return this->m_AirportPtr[index];
	}
	return Airport();
}

sdds::AirportLog::operator size_t() const
{
	return this->m_count;
}

sdds::AirportLog::AirportLog(const AirportLog& rhs)
{
	*this = rhs;
}

sdds::AirportLog& sdds::AirportLog::operator=(const AirportLog& rhs)
{
	//Step 1: Check for self-assessment
	if (this != &rhs)
	{
		//Step 2: Cleanup
		delete[] this->m_AirportPtr;

		//Step 3: Shallow Cpy
		this->m_count = rhs.m_count;

		//Step 4: Deep copy
		if (rhs.m_AirportPtr != nullptr)
		{
			//Copy data:
			this->m_AirportPtr = new sdds::Airport[this->m_count + 1];
			for (size_t i = 0; i < rhs.m_count; ++i)
			{
				this->m_AirportPtr[i] = rhs.m_AirportPtr[i];
			}
		}
		else
		{
			this->m_AirportPtr = nullptr;
		}
	}

	return *this;
}

sdds::AirportLog::AirportLog(sdds::AirportLog&& rhs)
{
	*this = std::move(rhs);
}

sdds::AirportLog& sdds::AirportLog::operator=(AirportLog&& rhs)
{
	//Step 1: Check for Self-Assessment
	if (this != &rhs)
	{
		//Step 2: Cleanuo
		delete[] this->m_AirportPtr;

		//Step 3: Shallow Copy
		this->m_count = rhs.m_count;

		//Step 4: Move resource(s)
		this->m_AirportPtr = rhs.m_AirportPtr;
		rhs.m_count = 0;
		rhs.m_AirportPtr = nullptr;
	}

	return *this;
}

sdds::AirportLog::~AirportLog()
{
	delete[] this->m_AirportPtr;
}