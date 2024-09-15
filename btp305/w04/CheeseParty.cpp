#include "CheeseParty.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds
{
	//------ Constructor
	CheeseParty::CheeseParty()
	{}

	CheeseParty::CheeseParty(const CheeseParty& rhs)
	{
		*this = rhs;
	}

	CheeseParty::CheeseParty(CheeseParty&& rhs)
	{
		*this = std::move(rhs);
	}



	//------ Destructor
	CheeseParty::~CheeseParty()
	{
		delete[] this->m_pCheeses;
	}



	//------ Add + Remove Functions
	CheeseParty& CheeseParty::addCheese(const Cheese& rhs)
	{
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			if (this->m_pCheeses[i] == &rhs)
			{
				return *this;
			}
		}

		const Cheese** temp = new const Cheese * [this->m_cnt + 1];
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			temp[i] = this->m_pCheeses[i];
		}
		temp[this->m_cnt] = &rhs;	

		delete[] this->m_pCheeses;
		this->m_pCheeses = temp;
		++this->m_cnt;
		return *this;
	}


	CheeseParty& CheeseParty::removeCheese()
	{
		if (this->m_cnt == 0)
			return *this;

		//# of Cheese's with 0 weight
		int cnt{};
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			if (this->m_pCheeses[i]->getWeight() == 0)
			{
				++cnt;
			}
		}

		//Create temporary array
		const Cheese** tmp = new const Cheese * [this->m_cnt - cnt];
		
		//add all cheese with > 0 weight to new array
		unsigned index{};
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			if (this->m_pCheeses[i]->getWeight() != 0)
			{
				tmp[index] = this->m_pCheeses[i];
				++index;
			}
		}

		//assign the new array into the orignal one
		delete[] this->m_pCheeses;
		this->m_pCheeses = tmp;
		this->m_cnt -= cnt;

		return *this;
	}

	//------ Assignment Operators
	//Copy Assignment
	CheeseParty& CheeseParty::operator=(const CheeseParty& rhs)
	{
		if (this != &rhs)
		{
			//cleanup
			delete[] this->m_pCheeses;

			//shallow cpy
			this->m_cnt = rhs.m_cnt;

			//deepy cpy
			this->m_pCheeses = new const Cheese * [rhs.m_cnt];
			for (auto i = 0u; i < rhs.m_cnt; ++i)
			{
				this->m_pCheeses[i] = rhs.m_pCheeses[i];
			}

		}

		return *this;
	}
	
	//Move Assignment
	CheeseParty& CheeseParty::operator=(CheeseParty&& rhs)
	{
		if (this != &rhs)
		{
			delete[] this->m_pCheeses;

			this->m_cnt = rhs.m_cnt;
			this->m_pCheeses = rhs.m_pCheeses;

			rhs.m_pCheeses = nullptr;
			rhs.m_cnt = 0;
		}
		return *this;
	}

	
	//Queries

	size_t CheeseParty::getCount() const
	{
		return this->m_cnt;
	}

	//print function
	std::ostream& CheeseParty::print(std::ostream& ostr) const
	{
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			ostr << *(this->m_pCheeses[i]);
		}
		return ostr;
	}


	//Helper Function
	std::ostream& operator<<(std::ostream& ostr, const CheeseParty& rhs)
	{
		ostr << "--------------------------\nCheese Party"
			<< "\n--------------------------\n";
		if (!rhs.getCount())
		{
			ostr << "This party is just getting started!\n" << "--------------------------\n";
			return ostr;
		}
		rhs.print(ostr);
		return ostr << "--------------------------\n";
	}

}