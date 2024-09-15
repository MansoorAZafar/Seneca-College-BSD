#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include <vector>
#include "Resource.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	class Directory : public Resource
	{
	private:
		std::vector<Resource*> m_contents{};
		Resource* findRecursive(const std::string& name, const std::vector<OpFlags>& flag, Resource* resource); // added by me
	public:

		Directory() = default;
		Directory(const char* dirname);
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
		Directory& operator+=(Resource*);
		Resource* find(const std::string&, const std::vector<OpFlags>& = {});

		void remove(const std::string&, const std::vector<OpFlags>& = {});
		void display(std::ostream&, const std::vector<FormatFlags> & = {}) const;


		Directory(const Directory&) = delete;
		Directory& operator=(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator=(Directory&&) = delete;
		
		~Directory();

	};
}

#endif