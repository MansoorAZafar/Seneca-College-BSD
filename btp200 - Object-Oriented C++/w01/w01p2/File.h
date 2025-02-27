#ifndef SDDS_FILE_H
#define SDDS_FILE_H

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 

namespace sdds {

	void closeFile(const char filename[]);
	bool openFile(const char filename[]);
	void findMatch(int& counter, double& val);
	void findLess(int& counter, double& val);
	void findGreater(int& counter, double& val);
	void setValues(int& counter);
	void sort(int& length);
	void swap(int& pos1, int& pos2);


}

#endif