#ifndef SDDS_NAMETAG_H
#define SDDS_NAMETAG_H

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 26, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	class NameTag {
	private:
		char* name = nullptr;
		int digit = 0;
	public:
		NameTag();
		NameTag(const char* str);
		NameTag(const char* str, int val);
		~NameTag();
		void print() const;
		NameTag& read();
	};

}

#endif