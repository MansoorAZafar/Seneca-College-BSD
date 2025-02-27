#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include "Book.h"
//#define log(x) std::cout << "DEBUG :: " << #x << " :: " << x << std::endl;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	//=========================================================================================================
	//======== CLASS ========//
	//=========================================================================================================

	template <class T, unsigned C>
	class Collection
	{
	private:
		T m_items[C]{};
		unsigned m_capacity{ C };
		unsigned m_size{};
		T m_smallestItem{};
		T m_largestItem{};
		T tmp{};
	protected:
		void setSmallestItem(const T& item);
		void setLargestItem(const T& item);

		void incrSize();
	public:
		T& operator[](unsigned index);
		Collection();

		T getSmallestItem() const;
		T getLargestItem() const;

		auto size() const;
		auto capacity() const;
		std::ostream& print(std::ostream& ostr) const;
		bool operator+=(const T& item);

	};

	//=========================================================================================================
	//======== END OF CLASS ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== ACCESSORS ========//
	//=========================================================================================================

	template<class T, unsigned C>
	T Collection<T, C>::getSmallestItem() const
	{
		return this->m_smallestItem;
	}

	template<class T, unsigned C>
	T Collection<T, C>::getLargestItem() const
	{
		return this->m_largestItem;
	}

	template<class T, unsigned C>
	auto Collection<T, C>::size() const
	{
		return this->m_size;
	}

	template<class T, unsigned C>
	auto Collection<T, C>::capacity() const
	{
		return this->m_capacity;
	}

	//=========================================================================================================
	//======== END OF ACCESSORS ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== MUTATORS ========//
	//=========================================================================================================

	template<class T, unsigned C>
	void Collection<T, C>::setSmallestItem(const T& item)
	{
		this->m_smallestItem = item;
	}

	template<class T, unsigned C>
	void Collection<T, C>::setLargestItem(const T& item)
	{
		this->m_largestItem = item;
	}

	template<class T, unsigned C>
	void Collection<T, C>::incrSize()
	{
		++this->m_size;
	}

	//=========================================================================================================
	//======== END OF MUTATORS ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== CONSTRUCTOR ========//
	//=========================================================================================================

	template<class T, unsigned C>
	Collection<T, C>::Collection() : m_smallestItem(9999), m_largestItem(-9999)
	{}

	//=========================================================================================================
	//======== END OF CONSTRUCTOR ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== PRINTING ========//
	//=========================================================================================================

	template<class T, unsigned C>
	std::ostream& Collection<T, C>::print(std::ostream& ostr) const
	{
		ostr << "[";
		for (auto i = 0u; i < this->m_size; ++i)
		{
			if (i < m_size - 1)
			{
				ostr << this->m_items[i] << ",";
			}
			else
			{
				ostr << this->m_items[i];
			}
		}
		ostr << "]";
		return ostr << std::endl;
	}

	//=========================================================================================================
	//======== END OF PRINTING ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== OPERATORS ========//
	//=========================================================================================================

	//Operator []

	template<class T, unsigned C>
	T& Collection<T, C>::operator[](unsigned index)
	{
		if (index < 0 || index >= this->capacity())
		{
			return this->tmp;
		}
		return this->m_items[index];
	}


	//Operator +=
	template<class T, unsigned C>
	bool Collection<T, C>::operator+=(const T& item)
	{
		if (this->m_size == this->m_capacity)
		{
			return false;
		}

		this->m_items[this->m_size] = item;
		this->incrSize();

		//Set Largest + Smallest
		//Assume obj T has < > + bool operator

		if (!this->getSmallestItem())
		{
			this->setSmallestItem(this->m_items[this->m_size - 1]);
			this->setLargestItem(this->m_items[this->m_size - 1]);
		}

		for (auto i = 0u; i < this->m_size; ++i)
		{
			if (this->m_items[i] < this->getSmallestItem())
			{
				this->setSmallestItem(this->m_items[i]);
			}
			if (this->m_items[i] > this->getLargestItem())
			{
				this->setLargestItem(this->m_items[i]);
			}
		}

		return true;
	}

	//=========================================================================================================
	//======== END OF OPERATORS ========//
	//=========================================================================================================


	//=========================================================================================================
	//======== SPECIALIZATIONS ========//
	//=========================================================================================================

	template<>
	Collection<Book, 10>::Collection()
	{
		this->setSmallestItem(Book("", 1, 10000));
		this->setLargestItem(Book("", 10000, 1));
	}

	template<>
	Collection<Book, 72>::Collection()
	{
		this->setSmallestItem(Book("", 1, 10000));
		this->setLargestItem(Book("", 10000, 1));
	}

	template<>
	std::ostream& Collection<Book, 10>::print(std::ostream& ostr) const
	{
		ostr << "| ---------------------------------------------------------------------------|" << std::endl;
		for (auto i = 0u; i < this->m_size; ++i)
		{
			ostr << "| ";
			this->m_items[i].print(ostr) << " |\n";
		}
		ostr << "| ---------------------------------------------------------------------------|" << std::endl;
		return ostr;
	}

	template<>
	std::ostream& Collection<Book, 72>::print(std::ostream& ostr) const
	{
		ostr << "| ---------------------------------------------------------------------------|" << std::endl;
		for (auto i = 0u; i < this->m_size; ++i)
		{
			ostr << "| ";
			this->m_items[i].print(ostr) << " |\n";
		}
		ostr << "| ---------------------------------------------------------------------------|" << std::endl;
		return ostr;
	}

	//=========================================================================================================
	//======== END OF SPECIALIZATIONS ========//
	//=========================================================================================================
}

#endif