#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 23, 2023
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

	std::ostream& operator<<(std::ostream&, const Airport);

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
		//Rule of 3


		~AirportLog();
	};
}
#endif