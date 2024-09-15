#ifndef SDDS_FILE_H
#define SDDS_FILE_H
#include <string_view>
#include "Resource.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{

	class File : public Resource
	{
		std::string_view m_contents{};
	public:
		File() = default;
		File(const char* filename, const char* repersentation = "");
		void update_parent_path(const std::string& path);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
	};

}

#endif