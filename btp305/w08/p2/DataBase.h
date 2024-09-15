#ifndef SDDS_DATABASE_H
#define SDDS_DATABASE_H
// Workshop 8 - Smart Pointers

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | November 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template <typename T>
	class DataBase {
		std::vector<T> database;
	public:
		DataBase() { }
		DataBase(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
			while (file) {
				T e;
				try {
					if (e.load(file))
						database.push_back(T(e));
				}
				catch (...) {
					break;
				}
			}
		}
		size_t size() const { return database.size(); }
		const T& operator[](size_t i) const { return database[i]; }

		// TODO: Overload the += operator with a raw pointer
		//       as a second operand.

		DataBase& operator+=(T* obj)
		{
			this->database.push_back(*obj);
			return *this;
		}

		// TODO: Overload the += operator with a smart pointer
		//       as a second operand.

		DataBase& operator+=(std::unique_ptr<T>& obj)
		{
			this->database.push_back(*obj);
			return *this;

		}

		void display(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : database)
				os << e;
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const DataBase<T>& db) {
		db.display(os);
		return os;
	}
}
#endif