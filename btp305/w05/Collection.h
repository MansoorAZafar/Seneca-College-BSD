#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include <string>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 14, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	template <class T>
	class Collection
	{
		T* m_arr{};
		std::string m_name{};
		size_t m_cnt{};
		void (*observer)(const Collection<T>&, const T&) = nullptr;

	public:

		Collection(const std::string& name);

		//deleted functions
		Collection(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;

		~Collection();

		const std::string& name() const;
		size_t size() const;

		void setObserver(void (*observer)(const Collection<T>& collection, const T& item));
		Collection<T>& operator+=(const T& item);

		T& operator[](size_t idx) const;
		T* operator[](const std::string& title) const;
	};

	template <class T>
	std::ostream& operator<<(std::ostream& ostr, const Collection<T>& rhs);


	//Definitions:
	//Constructor
	template <class T>
	Collection<T>::Collection(const std::string& name) : m_name(name)
	{}


	//Destructor
	template <class T>
	Collection<T>::~Collection()
	{
		delete[] this->m_arr;
	}

	
	//Queries
	template <class T>
	const std::string& Collection<T>::name() const
	{
		return this->m_name;
	}

	template <class T>
	size_t Collection<T>::size() const
	{
		return this->m_cnt;
	}


	//Mutator
	template <class T>
	void Collection<T>::setObserver(void (*observer)(const Collection<T>& collection, const T& item))
	{
		this->observer = observer;
	}

	
	// Operators[]
	template <class T>
	Collection<T>& Collection<T>::operator+=(const T& item)
	{
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			if (this->m_arr[i].title() == item.title())
			{
				return *this;
			}
		}

	
		T* arr = new T[this->m_cnt + 1];
		for (auto i = 0u; i < this->m_cnt; ++i)
			arr[i] = this->m_arr[i];

		arr[this->m_cnt] = item;
		++this->m_cnt;

		if (this->observer != nullptr)
		{
			this->observer(*this, item);
		}


		delete[] this->m_arr;
		this->m_arr = arr;
		return *this;
	}

	template <class T>
	T& Collection<T>::operator[](size_t idx) const
	{
		if (idx >= this->m_cnt)
			throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(this->m_cnt) + "] items.");
		return this->m_arr[idx];

	}

	template <class T>
	T* Collection<T>::operator[](const std::string& title) const
	{
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			if (this->m_arr[i].title() == title)
			{
				return &this->m_arr[i];
			}
		}
		return nullptr;
	}

	template <class T>
	std::ostream& operator<<(std::ostream& ostr, const Collection<T>& collection)
	{
		for (auto i = 0u; i < collection.size(); ++i)
		{
			ostr << collection.operator[](i);
		}
		return ostr;
	}

}

#endif