#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
// Workshop 8 - Smart Pointers

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | November 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#include "DataBase.h"
#include "Profile.h"

namespace sdds
{
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
}

#endif