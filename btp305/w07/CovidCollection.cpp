#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iomanip>
#include "CovidCollection.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | November 11, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{ 

	void CovidCollection::trim(std::string& str) noexcept
	{
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");
		str = std::move(str.substr(start, end - start + 1));
	}

	constexpr unsigned int LINE_LENGTH = 90; 	
	//25 for country, + 25 for city, + 25 for varient = atleast length of 75 + 5,5,5 for year,case,death = length should be 90

	CovidCollection::CovidCollection(const char* filename)
	{
		std::ifstream file(filename);
		if (file.fail())
			throw std::invalid_argument("File does not exist...");

		std::string line{};
		while (file)
		{
			std::getline(file, line);
			if (file)
			{
				if (line.length() != LINE_LENGTH)
				{
					//If the length is not the same length then theres something wrong with the file
					Covid covid{};
					//Grabs a string from 0 to length n and erases it so the next part will start from 0
					auto getNCharFromStr = [&](const int& length) noexcept -> std::string
						{
							std::string result{};
							result = line.substr(0, length);
							line.erase(0,length);
							this->trim(result);
							return result;
						};
					covid.m_country = std::move(getNCharFromStr(25));
					covid.m_city = std::move(getNCharFromStr(25));
					covid.m_variant = std::move(getNCharFromStr(25));
					covid.m_year = std::stoi(getNCharFromStr(5));
					covid.m_cases = std::stoul(getNCharFromStr(5));
					covid.m_deaths = std::stoul(getNCharFromStr(5));

					this->m_covidInfo.push_back(std::move(covid));
				}
			}
		}
	}


	//TODO: add the percents of info
	void CovidCollection::display(std::ostream& ostr, const std::string& country) const
	{
		unsigned int totalDeaths = std::accumulate(this->m_covidInfo.begin(), this->m_covidInfo.end(), 0u, [](const unsigned int& sumDeaths, const Covid& info)
			{return sumDeaths + info.m_deaths; });
		unsigned int totalCases = std::accumulate(this->m_covidInfo.begin(), this->m_covidInfo.end(), 0u, [](const unsigned int& sumCases, const Covid& info)
			{return sumCases + info.m_cases; });

		if (country != "ALL")
		{
			///*************************///
			/// IF COUNTRY ISNT "ALL"   ///
			///*************************///
			ostr << "Displaying information of country = " << country << "\n";
			//allowed to send the stream by ref:  "the stream object is the only one allowed to be captured by reference"
			std::for_each(this->m_covidInfo.begin(), this->m_covidInfo.end(), [=, &ostr](const Covid& item)
				{
					if (country == item.m_country)
						ostr << item << "\n";
				});

			unsigned int sumDeaths = std::accumulate(this->m_covidInfo.begin(), this->m_covidInfo.end(), 0u, [country](const unsigned int& sumDeaths, const Covid& info) 
				{
					if(country == info.m_country)
						return sumDeaths + info.m_deaths;
					return sumDeaths;
				});
			unsigned int sumCases = std::accumulate(this->m_covidInfo.begin(), this->m_covidInfo.end(), 0u, [country](const unsigned int& sumCases, const Covid& info)
				{
					if(country == info.m_country)
						return sumCases + info.m_cases;
					return sumCases;
				});

			double globalDeaths = (double)sumDeaths / totalDeaths * 100.0;
			double globalCases = (double)sumCases / totalCases * 100.0;

			std::string caseData = "Total cases in " + country + ": " + std::to_string(sumCases);
			std::string deathData = "Total deaths in " + country + ": " + std::to_string(sumDeaths);
			std::string globalData = country + " has " + std::to_string(globalCases) + "% of global cases and "
				+ std::to_string(globalDeaths) + "% of global deaths";

			//From the main func -> printbar
			ostr << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');

			ostr << "|" << std::setw(85) << std::right << caseData << " |\n"
				 << "|" << std::setw(85) << deathData << " |\n"
				 << "|" << std::setw(85) << globalData << " |\n";
			return;
		}

		///*************************///
		///    IF ALL COUNTRIES     ///
		///*************************///

		std::for_each(this->m_covidInfo.begin(), this->m_covidInfo.end(), [=, &ostr](const Covid& item)
			{
				ostr << item << "\n";
			});

		std::string caseData = "Total cases around the world: " + std::to_string(totalCases);
		std::string deathData = "Total deaths around the world: " + std::to_string(totalDeaths);
		
		ostr << "|" << std::setw(85) << std::right << caseData << " |\n"
			 << "|" << std::setw(85) << deathData << " |\n";
	}

	std::ostream& operator<<(std::ostream& ostr, const Covid& theCovid)
	{
		std::string year = theCovid.m_year < 0 ? "" : std::to_string(theCovid.m_year);
		std::string cases = theCovid.m_cases < 0 ? "" : std::to_string(theCovid.m_cases);
		std::string deaths = theCovid.m_deaths < 0 ? "" : std::to_string(theCovid.m_deaths);
		
		ostr << "| " << std::left << std::setw(21) << theCovid.m_country << " | " <<
			std::setw(15) << theCovid.m_city << " | " <<
			std::setw(20) << theCovid.m_variant << " | " << std::right << 
			std::setw(6) << year << " | " << 
			std::setw(4) << cases << " | " <<
			std::setw(3) << deaths << " | | " << 
			std::setw(8) << theCovid.status << " |";
		return ostr;
	}

	void CovidCollection::sort(const std::string& field)
	{	
		std::sort(this->m_covidInfo.begin(), this->m_covidInfo.end(), [=](const Covid& first, const Covid& second)
			{
				if (field == "country")
				{
					if (first.m_country != second.m_country)
						return first.m_country < second.m_country;
					return first.m_deaths < second.m_deaths;
				}
				if (field == "variant")
				{
					if (first.m_variant != second.m_variant)
						return first.m_variant < second.m_variant;
					return first.m_deaths < second.m_deaths;
				}
				if (field == "city")
				{
					if (first.m_city != second.m_city)
						return first.m_city < second.m_city;
					return first.m_deaths < second.m_deaths;
				}
				if (field == "cases")
				{
					if (first.m_cases != second.m_cases)
						return first.m_cases < second.m_cases;
					return first.m_deaths < second.m_deaths;
				}
				if (field == "year")
				{
					if (first.m_year != second.m_year)
						return first.m_year < second.m_year;
					return first.m_deaths < second.m_deaths;
				}
				return first.m_deaths < second.m_deaths;
			});
	}

	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		return std::any_of(this->m_covidInfo.begin(), this->m_covidInfo.end(), [=](const Covid& info)
			{
				return info.m_country == country && info.m_variant == variant && info.m_deaths >= deaths;
			});
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		auto size = std::count_if(this->m_covidInfo.begin(), this->m_covidInfo.end(), [=](const Covid& info) {return info.m_deaths >= deaths; });
		std::list<Covid> listOfDeaths(size);

		std::copy_if(this->m_covidInfo.begin(), this->m_covidInfo.end(), listOfDeaths.begin(), [=](const Covid& info) { return info.m_deaths >= deaths; });
		return listOfDeaths;
	}

	void CovidCollection::updateStatus()
	{
		std::transform(this->m_covidInfo.begin(), this->m_covidInfo.end(), this->m_covidInfo.begin(), [](Covid& info)
			{
				info.status = info.m_deaths > 50 ? info.m_deaths > 300 ? "EPIDEMIC" : "MILD" : "EARLY";
				return info;
			});
	}

}
