#include <fstream>
#include <cstring>
#include "File.h"
#include "Filesystem.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | October 30, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds
{
	void Filesystem::add(const std::string& path, const std::string& content)
	{
		std::string str = path;
		size_t cntDir{};
		auto position = str.find("/");
		while (position != std::string::npos)
		{
			++cntDir;
			position = str.find("/", position + 1);
		}

		//WE have number of directories + how to get file
		this->m_current = this->m_root;

		for (auto i = 0u; i < cntDir; ++i)
		{
			position = 0u; // no whitespace so position should always be at the start of the string
			auto endPosition = str.find_first_of('/');
			std::string dirName = str.substr(position, endPosition - position + 1);

			//Create a new directory
			Directory* dir = new Directory(dirName.c_str());

			//add onto
			try
			{
				//if different directory: add it
				this->operator+=(dir);
				if (i == 0)
					this->m_current->update_parent_path("/");
				this->m_current = dir;
			}
			catch (...)
			{
				//if directory already exists -> set it to existing one (if exists)
				delete dir;
				this->m_current = dynamic_cast<Directory*>(this->m_root->find(dirName));
				if (i == 0)
					this->m_current->update_parent_path("/");
			}	
			str.erase(position, endPosition+1);
		}

		if (!str.empty())
		{
			File* file = new File(str.c_str(), content.c_str());
			try
			{
				file->update_parent_path(path);
				this->operator+=(file);

			}
			catch (...)
			{
				delete file;
			}
		}
		this->m_current = this->m_root; // at the end we are adding to the root so current should end in the root for the constructor
	}


	Filesystem::Filesystem(const char* filename, const char* rootDir)
	{
		//member first creates a dynamically allocated Directory object to set as the root + current
		Directory* tmp = new Directory(rootDir);
		this->m_root = tmp;

		std::string content{};
		std::string path{};

		std::ifstream ifstr(filename);
		if (ifstr.fail())
		{
			delete tmp;
			throw std::invalid_argument("File doesn't exist");
		}
		std::string line{};
		while (ifstr)
		{
			std::getline(ifstr, line);
			if (ifstr)
			{
				auto pos = line.find("|");
				if (pos == std::string::npos)
					pos = line.find("\n");

				path = line.substr(0, pos);
				line.erase(0,pos+1);

				//fix whitespace
				pos = path.find_first_not_of(" ");
				auto posEnd = path.find_last_not_of(" ");
				path = path.substr(pos, posEnd - pos + 1);
				
				if (line.empty())
				{
					this->add(path);
				}
				else
				{
					//there is a description
					pos = line.find('\n');
					content = line.substr(0,pos);
				
					//Fix whitespace
					pos = content.find_first_not_of(" ");
					posEnd = content.find_last_not_of(" ");
					content = content.substr(pos, posEnd-pos + 1);

					this->add(path, content);

				}

			}
		}
	}

	Filesystem::Filesystem(Filesystem&& other) noexcept
	{
		*this = std::move(other);
	}

	Filesystem& Filesystem::operator=(Filesystem&& other) noexcept
	{
		if (this == &other)
			return *this;

		delete this->m_root;
		this->size = 0;

		this->m_current = other.m_current;
		this->m_root = other.m_root;
		this->size = other.size;

		other.m_current = nullptr;
		other.m_root = nullptr;
		other.size = 0;

		return *this;
	}

	Filesystem& Filesystem::operator+=(Resource* resource)
	{
		this->m_current->operator+=(resource);
		return *this;
	}

	Directory* Filesystem::change_directory(const std::string& dir)
	{
		if (dir.empty())
			return (this->m_current = this->m_root);
		
		std::vector<OpFlags> flag;
		flag.push_back(OpFlags::RECURSIVE);

		if (this->m_root->find(dir, flag) == nullptr)
			throw std::invalid_argument("Cannot change the directory! not found!");

		if (this->m_root->find(dir, flag))
		{
			this->m_current = dynamic_cast<Directory*>(this->m_root->find(dir, flag));
			return this->m_current;
		}

		return nullptr;
	}

	Directory* Filesystem::get_current_directory() const
	{
		return this->m_current;
	}

	Filesystem::~Filesystem()
	{
		delete this->m_root;
	}

}