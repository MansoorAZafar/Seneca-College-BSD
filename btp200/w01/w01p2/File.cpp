#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "GPA.h"
#include "File.h"
using namespace std;

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments. 

namespace sdds {
#define MAX_STUDENTS 100 
	FILE* fp;
	struct GPA arr[MAX_STUDENTS];

	bool openFile(const char filename[]) {
		fp = fopen(filename, "r");
		return fp != NULL; // returns true if not NULL
	}

	void closeFile(const char filename[]) {
		fclose(fp);
	}

	void findMatch(int& counter, double& val) {
		bool exists = false; // Set a flag to false incase no student exists with the gpa
		int pos = 1;
		for (int i = 0; i < counter; i++) {
			if (arr[i].gpa == val) {
				//Check the the students gpa is equal the one provided
				cout << "[" << pos << "] " << arr[i].stno << ": " << fixed << setprecision(1) << arr[i].gpa << " (" << arr[i].name << ")\n"; exists = true; //Print it out if true
				pos++;
			}
		}
		if (!exists) {
			cout << "There is no student with that gpa.\n"; // If no student exist with set gpa
		}
	}


	void findLess(int& counter, double& val) {
		//sort(counter);
		//Same concept as findMatch() But instead of equal it's checking if its less
		bool exists = false;
		int pos = 1;
		for (int i = 0; i < counter; i++) {
			if (arr[i].gpa < val) {
				cout << "[" << pos << "] " << arr[i].stno << ": " << fixed << setprecision(1) << arr[i].gpa << " (" << arr[i].name << ")\n"; exists = true;
				pos++;
			}
		}
		if (!exists) {
			cout << "There is no student with that gpa.\n";
		}
	}

	void findGreater(int& counter, double& val) {
		//Same concept as findMatch() But instead of equal it's checking if its greater
		bool exists = false;
		int pos = 1;
		for (int i = 0; i < counter; i++) {
			if (arr[i].gpa > val) {
				cout << "[" << pos << "] " << arr[i].stno << ": " << fixed << setprecision(1) << arr[i].gpa << " (" << arr[i].name << ")\n"; exists = true;
				pos++;
			}
		}
		if (!exists) {
			cout << "There is no student with that gpa.\n";
		}
	}

	void swap(int& pos1, int& pos2) {
		//cout << "I happened";
		struct GPA temp = arr[pos1];
		arr[pos1] = arr[pos2];
		arr[pos2] = temp;
	}

	void sort(int& length) {
		//bubble sort 
		for (int i = 0; i < length - 1; i++) {
			for (int j = 0; j < length - i - 1; j++) {
				if (arr[j].stno > arr[j + 1].stno) {
					int pos = j + 1;
					swap(j, pos);
				}
			}
		}
	}

	void setValues(int& counter) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			//To go through each student
			if (fscanf(fp, "%[^,],%d,%lf\n", arr[i].name, &arr[i].stno, &arr[i].gpa) == 3) {
				//Scan the respective needed variables/content
				counter++; // increase the counter var
				//cout << "Counter is : " << counter;
			}
		}
		//Sort
		sort(counter);
	}

}