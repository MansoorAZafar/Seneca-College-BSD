#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <iostream>
#include <vector>
#include <list>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | November 11, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{

	struct Covid
	{
		std::string m_country{}; // not modified outside of initalization
		std::string m_city{};	// not modified outside of initalization
		std::string m_variant{};	// not modified outside of initalization
		int m_year{}; 
		unsigned int m_cases{};
		unsigned int m_deaths{};
		std::string status{"General"};

	}; 

	class CovidCollection
	{
	private:
		std::vector<Covid> m_covidInfo{};
		void trim(std::string& str) noexcept;
	public:
		CovidCollection() = default;
		CovidCollection(const char* filename);
		void display(std::ostream& ostr, const std::string& country = "ALL") const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();

	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
	
}

#endif