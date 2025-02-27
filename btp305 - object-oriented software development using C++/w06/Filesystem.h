#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include "Directory.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{

	class Filesystem
	{
	private:

		Directory* m_root{};
		Directory* m_current{};
		void add(const std::string& name, const std::string& content = ""); //added by me
		size_t size{};
	public:

		Filesystem() = default;
		Filesystem(const char* filename, const char* rootDir = "");

		//Delete copy operations
		Filesystem(const Filesystem&) = delete;
		Filesystem& operator=(const Filesystem&) = delete;

		//support move operations
		Filesystem(Filesystem&&) noexcept;
		Filesystem& operator=(Filesystem&&) noexcept;

		Filesystem& operator+=(Resource*);

		Directory* change_directory(const std::string& = "");
		Directory* get_current_directory() const;

		~Filesystem();
	};

	




}

#endif