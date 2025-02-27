#include "File.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	File::File(const char* filename, const char* repersentation)
	{
		
		this->m_contents = repersentation;
		Resource::m_name = filename;
		this->update_parent_path(filename);
	}

	void File::update_parent_path(const std::string& path)
	{
		Resource::m_parent_path = path + this->name();
	}

	NodeType File::type() const
	{
		return NodeType::FILE;
	}

	std::string File::path() const
	{
		return Resource::m_parent_path;
	}

	std::string File::name() const
	{
		return Resource::m_name;
	}

	int File::count() const
	{
		return -1;
	}

	//Queries
	size_t File::size() const	
	{ 
		return this->m_contents.length(); 
	}

}