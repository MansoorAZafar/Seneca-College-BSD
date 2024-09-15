#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H
#include <iostream>
// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	class Cheese
	{
	private:

		std::string m_name{"NaC"};
		size_t m_weight{};
		double m_price{};
		std::string m_features{};

	public:

		//Constructuros
		Cheese();
		Cheese(const std::string& str);
		Cheese slice(const size_t& weight);

		std::string getName() const;
		size_t getWeight() const;
		double getPrice() const;
		std::string getFeatures() const;

		Cheese(const Cheese& rhs);
		Cheese& operator=(const Cheese& rhs);

	};
	std::ostream& operator<<(std::ostream& ostr, const Cheese& cheese);
}

#endif
