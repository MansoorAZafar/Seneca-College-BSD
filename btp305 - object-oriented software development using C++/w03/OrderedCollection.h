#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H
#include "Collection.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	constexpr unsigned capacity = 72;
	template <class T>
	class OrderedCollection : public Collection<T, capacity>
	{
	public:
		bool operator+=(const T& item);
	};

	template<class T>
	bool OrderedCollection<T>::operator+=(const T& item)
	{
		Collection<T, capacity>::operator+=(item);
		for (auto i = 0u; i < this->size() - 1; ++i)
		{
			for (auto j = i; j < this->size(); ++j)
			{
				if (this->operator[](i) > this->operator[](j))
				{
					//Swap
					T tmp = this->operator[](i);
					this->operator[](i) = this->operator[](j);
					this->operator[](j) = tmp;
				}
			}
		}
		return false;
	}
}

#endif