#ifndef SDDS_TOYS_H
#define SDDS_TOYS_H
#define MAX_TNAME 31

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {

	class Toys {
	private:
		char m_tname[MAX_TNAME];
		double m_price = 0.0;
		int m_age = 0;
		bool m_onSale = false;
	public:
		void addToys(const char* tname, int sku, double price, int age);
		void isSale(bool sale);
		void calSale();
		void display()const;
		int m_sku; // Questionable ig Idk if this should be public OR if I should just make a setter f(x)
	};


}


#endif // !