#ifndef SDDS_TOOLS_H_
#define SDDS_TOOLS_H_

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
	int openFile_r(const char filename[]); // Provided
	void closefile(); // Provided
	int noOfTraces(); // Provided

	// ADD: Declare read prototypes (4 prototypes)
	char* read(char* str);
	bool read(int& data);//, int& dayofyear, int& Fwifitime, int& Fctime);
	double& read(double& timeIH);
	char& read(char& day);



	void strCpy(char* des, const char* src); // Provided
	int strLen(const char* s); // Provided
}
#endif