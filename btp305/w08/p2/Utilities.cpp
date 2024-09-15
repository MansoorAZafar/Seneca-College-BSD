// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | November 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

#include <memory>
#include <utility>
#include <functional>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.

		for (size_t index = 0u; index < allProfiles.size(); ++index)
		{
			bool found{ false };

			for (size_t indx = 0u; indx < bannedProfiles.size(); ++indx)
			{
				if (bannedProfiles[indx].m_age == allProfiles[index].m_age && bannedProfiles[indx].m_name.first_name == allProfiles[index].m_name.first_name && bannedProfiles[indx].m_name.last_name == allProfiles[index].m_name.last_name)
				{
					found = true;
					indx = bannedProfiles.size(); // no need to continue the loop
				}
			}
			
			if (!found)
			{
				Profile* current = new Profile(allProfiles[index].m_name, allProfiles[index].m_address, allProfiles[index].m_age);
				try
				{
					current->validateAddress(); // can throw exception
					result.operator+=(current);
					delete current;
				}
				catch (...)
				{
					delete current;
					throw std::string("*** Invalid Address ***");
				}
			}
		}
		return result;
	}

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Smart Pointers.


		for (size_t index = 0u; index < allProfiles.size(); ++index)
		{
			bool bad{ false };

			for (size_t indx = 0u; indx < bannedProfiles.size(); ++indx)
			{
				if (bannedProfiles[indx].m_age == allProfiles[index].m_age && bannedProfiles[indx].m_name.first_name == allProfiles[index].m_name.first_name && bannedProfiles[indx].m_name.last_name == allProfiles[index].m_name.last_name)
				{
					bad = true;
					indx = bannedProfiles.size(); // no need to continue the loop
				}
			}

			if (bad == false)
			{
				std::unique_ptr<Profile> currentProfile(new Profile(allProfiles[index].m_name, allProfiles[index].m_address, allProfiles[index].m_age));				
				try
				{
					currentProfile->validateAddress(); // can throw exception
					result.operator+=(currentProfile);
				}
				catch (...)
				{
					throw std::string("*** Invalid Address ***");
				}
			}
		}


		return result;
	}
}