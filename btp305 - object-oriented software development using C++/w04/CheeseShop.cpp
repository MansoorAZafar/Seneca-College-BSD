#include "CheeseShop.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 8, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.


namespace sdds 
{
	
	//----------- CONSTRUCTOR(S)
	//Construct with string argument
	CheeseShop::CheeseShop(const std::string& name) : m_Shopname(name)
	{}

	//Copy Constructor
	CheeseShop::CheeseShop(const CheeseShop& rhs)
	{
		*this = rhs;
	}
	
	//Move Constructor
	CheeseShop::CheeseShop(CheeseShop&& rhs)
	{
		*this = std::move(rhs);
	}



	//----------- Queries

	std::string CheeseShop::getShopName() const
	{
		return this->m_Shopname;
	}

	size_t CheeseShop::getCount() const
	{
		return this->m_cnt;
	}

	std::ostream& CheeseShop::print(std::ostream& ostr) const
	{
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			ostr << *(this->m_pCheeses[i]);
		}
		return ostr;
	}



	//----------- Operator=/Assignment overload(s)
	//Copy Assignment
	CheeseShop& CheeseShop::operator=(const CheeseShop& rhs)
	{
		//check for self-assessment .1
		if (this != &rhs)
		{
			//cleanup .2
			for(auto i = 0u; i < this->m_cnt; ++i)
			{
				delete this->m_pCheeses[i];
			}
			delete[] this->m_pCheeses;

			//shallow cpy .4
			this->m_cnt = rhs.m_cnt;
			this->m_Shopname = rhs.m_Shopname;

			//deep cpy
			this->m_pCheeses = new const Cheese * [rhs.m_cnt];
			for (auto i = 0u; i < rhs.m_cnt; ++i)
			{
				this->m_pCheeses[i] = new Cheese(*(rhs.m_pCheeses[i]));
			}
		}
		return *this;
	}

	//Move Assignment
	CheeseShop& CheeseShop::operator=(CheeseShop&& rhs)
	{
		//check for self-assessment .1
		if (this != &rhs)
		{
			//cleanup .2
			for(auto i = 0u; i < this->m_cnt; ++i)
				delete this->m_pCheeses[i];			
			delete[] this->m_pCheeses;

			//move
			this->m_cnt = rhs.m_cnt;
			this->m_pCheeses = rhs.m_pCheeses;
			this->m_Shopname = rhs.m_Shopname;

			//set other to empty
			rhs.m_pCheeses = nullptr;
			rhs.m_cnt = 0;
			rhs.m_Shopname = "";

		}
		return *this;
	}



	//----------- Add function

	CheeseShop& CheeseShop::addCheese(const Cheese& rhs)
	{
		const Cheese** tmp = new const Cheese * [this->m_cnt + 1];
		for (auto i = 0u; i < this->m_cnt; ++i)
		{
			tmp[i] = this->m_pCheeses[i];
		}
		tmp[this->m_cnt] = new Cheese(rhs);		
		delete[] this->m_pCheeses;
		this->m_pCheeses = tmp;
		++this->m_cnt;
		return *this;
	}



	//----------- Helper Operator

	std::ostream& operator<<(std::ostream& ostr, const CheeseShop& rhs)
	{
		ostr << "--------------------------\n" << rhs.getShopName()
			<< "\n--------------------------\n";
		if (!rhs.getCount())
		{
			ostr << "This shop is out of cheese!\n" << "--------------------------\n";
			return ostr;
		}
		rhs.print(ostr);
		return ostr << "--------------------------\n";
	}



	//----------- DESTRUCTOR
	
	CheeseShop::~CheeseShop()
	{
		for(auto i = 0u; i < this->m_cnt; ++i)
			delete this->m_pCheeses[i];
		delete[] this->m_pCheeses;
	}
}

