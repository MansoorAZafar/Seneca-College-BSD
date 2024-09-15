#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

extern double g_taxrate;
extern double g_discount;

namespace sdds
{
	class RideRequest
	{
	private:
		char m_customerName[10]{};
		char* m_description{};
		double m_price;
		bool m_discount{};
	public:
		RideRequest();
		std::istream& read(std::istream& istr);
		std::ostream& display(std::ostream& ostr = std::cout) const;
		~RideRequest();
		void setEmpty(); // added by me
		RideRequest& operator=(const RideRequest& rhs);
		RideRequest(const RideRequest& rhs);
	};
}

#endif