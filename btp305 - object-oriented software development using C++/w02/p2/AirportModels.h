#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 24, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{

	struct Airport
	{
		std::string m_code{};
		std::string m_name{};
		std::string m_city{};
		std::string m_state{};
		std::string m_country{};
		double m_latitude{};
		double m_longitude{};
	};

	std::ostream& operator<<(std::ostream&, const Airport&);

	class AirportLog
	{
	private:
		Airport* m_AirportPtr{};
		size_t m_count{};
	public:
		AirportLog();
		AirportLog(const char*);
		void addAirport(const sdds::Airport&);
		AirportLog findAirport(const char*, const char*) const;
		Airport operator[](size_t) const;
		operator size_t() const;
		//Rule of 5
		//Rule 1 & 2: - Copy Constructor + Operator:
		AirportLog(const AirportLog& rhs);
		AirportLog& operator=(const AirportLog& rhs);
		//Rule 3 & 4: - Move Constructor + Operator
		AirportLog(AirportLog&& rhs);
		AirportLog& operator=(AirportLog&& rhs);
		//Rule 5: Destructor
		~AirportLog();
	};
}
#endif