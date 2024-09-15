#include <iterator>
#include <iomanip>
#include "Directory.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	Directory::Directory(const char* dirname)
	{
		this->m_name = dirname;
		this->update_parent_path(dirname);
	}

	void Directory::update_parent_path(const std::string& dirname)
	{
		Resource::m_parent_path = dirname + this->name();
	}

	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}

	std::string Directory::path() const
	{
		return this->m_parent_path;
	}

	std::string Directory::name() const
	{
		return this->m_name;
	}

	int Directory::count() const
	{
		int cnt{}; // cus its an int not size_t 
		for (auto it = this->m_contents.begin(); it < this->m_contents.end(); ++it)
			++cnt;
		return cnt;
	}

	size_t Directory::size() const
	{
		size_t bytes {};
		for (auto i = 0u; i < this->m_contents.size(); ++i)
			bytes += sizeof(char) * this->m_contents[i]->size();
		return bytes;
	}

	Directory& Directory::operator+=(Resource* item)
	{
		for (auto file = 0u; file < this->m_contents.size(); ++file)
			if (this->find(item->name()))
				throw std::invalid_argument("Cannot add files with the same name"); // from the notes I thought this logically would fit ngl

		item->update_parent_path(this->path());
		this->m_contents.push_back(item);
		return *this;
	}

	/*
	FROM THE NOTES "Inheritance and Inclusion Polymorphism" : REFERENCE CODE
	bool Cube::operator==(const Shape& s) const
	{
		const Cube* c = dynamic_cast<const Cube*>(&s);
		return c ? len == c->len : false;
	}
	// Used to figure out how to use a directory function from a resource pointer
	// AHHH I SPENT SO LONG JUST TO USE DYNAMIC_CAST ( I KINDA WANTED ANOTHER WAY????)
	// BRUHHHHH gg
	*/
	Resource* Directory::findRecursive(const std::string& name, const std::vector<OpFlags>& flag, Resource* resource)
	{
		if (resource->name() == name)
			return resource;
		if (resource->type() == NodeType::DIR)
			return dynamic_cast<Directory*>(resource)->find(name, flag);

		return nullptr;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag)
	{
		if(!flag.empty())
			if (*(flag.begin()) == OpFlags::RECURSIVE)
			{
				Resource* tmp{};
				for (auto& resource : this->m_contents)
				{
					tmp = this->findRecursive(name, flag, resource);
					if (tmp != nullptr)
						return tmp;
				}
				return nullptr;
			}

		for (auto& it : this->m_contents)
			if (it->name() == name)
				return it;
		return nullptr;
	}

	void Directory::remove(const std::string& dirname, const std::vector<OpFlags>& flag)
	{
		if (this->find(dirname, flag) == nullptr)
			throw std::string(dirname + " does not exist in " + this->name());

		if (this->find(dirname, flag)->type() == NodeType::DIR && flag.empty())
			throw std::invalid_argument(dirname + " is a directory. Pass the recursive flag to delete directories.");

		size_t index{};
		auto iterator = this->m_contents.begin();
		for (auto it = this->m_contents.begin(); it < this->m_contents.end(); ++it)
		{
			if ((*it) == this->find(dirname, flag))
			{
				delete this->m_contents[index];
				iterator = it;
				it = this->m_contents.end()-1;
			}
			++index;
		}
		this->m_contents.erase(iterator);
		
	}

	void Directory::display(std::ostream& cout, const std::vector<FormatFlags>& flag) const
	{
		cout << "Total size: " << this->size() << " bytes\n";

		for (auto it = this->m_contents.begin(); it < this->m_contents.end(); ++it)
		{	
			std::string value = (*it)->count() >= 0 ? std::to_string((*it)->count()) : "";
			if(flag.empty())
				if ((*it)->type() == NodeType::DIR)
					cout << "D | " << std::left << std::setw(15) << (*it)->name() << " |";
				else
					cout << "F | " << std::left << std::setw(15) << (*it)->name() << " |";
			else
				if ((*it)->type() == NodeType::DIR)
					cout << "D | " << std::left << std::setw(15) << (*it)->name() << " |"
					<< std::right << std::setw(3) << value << " | "
					<< std::right << std::setw(4) << (*it)->size() << " bytes | ";
				else
					cout << "F | " << std::left << std::setw(15) << (*it)->name() << " |"
					<< std::right << std::setw(3) << value << " | "
					<< std::right << std::setw(4) << (*it)->size() << " bytes | ";
			cout << "\n";
		}
	}

	Directory::~Directory()
	{
		for (auto i = 0u; i < this->m_contents.size(); ++i)
			delete this->m_contents[i];
	}

}