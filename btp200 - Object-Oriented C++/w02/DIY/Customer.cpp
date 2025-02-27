#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "Customer.h"
#include "Tools.h"
#include <cstring>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | February 1, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds {
    // complete
    void read(char* str, int len) {  // Fully provided
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        cin.getline(str, len);
    }

    void EmptyRecord(Customers& c_rec){
        c_rec.likes_count = 0;
        c_rec.replies_count = 0;
        c_rec.retweets_count = 0;
        c_rec.share_videos = 0;
        c_rec.user_name[0] = '\0';
    }
    
    void EmptyRecord(CustomersRecord& t_rec) {
       
        t_rec.noOfRecords = 0;
        t_rec.ptr_rec = nullptr;
    }    

    void addCustomer(CustomersRecord& t_rec, const Customers& c_rec) {
	//delete[] t_rec.ptr_rec;
	int size = t_rec.noOfRecords + 1;
	Customers* tmp = new Customers[size];
	for(int i = 0; i < t_rec.noOfRecords; ++i){
		tmp[i] = t_rec.ptr_rec[i];
	}
	tmp[t_rec.noOfRecords] = c_rec;
	delete[] t_rec.ptr_rec;
	
	t_rec.ptr_rec = tmp;
	t_rec.noOfRecords = size;
	/* 
	//t_rec.ptr_rec = nullptr;
	t_rec.noOfRecords++;
        CustomersRecord temp = t_rec;
        t_rec.ptr_rec = new Customers[t_rec.noOfRecords];
        for (int i = 0; i < temp.noOfRecords-1; i++) {
            EmptyRecord(t_rec.ptr_rec[i]);	    
	    t_rec.ptr_rec[i] = temp.ptr_rec[i];
        }
        t_rec.noOfRecords = temp.noOfRecords;
        t_rec.ptr_rec[temp.noOfRecords - 1] = c_rec;
	*/    
	}
    
    void display(const Customers& c_rec) {
        cout << c_rec.user_name << ", " << c_rec.likes_count << ", " << c_rec.retweets_count << ", "
            << c_rec.replies_count << ", " << c_rec.share_videos << endl;
    }
    
    void display(const CustomersRecord& t_rec) {
        for (int i = 0; i < t_rec.noOfRecords; i++) {
            cout << i + 1 << ". "; display(t_rec.ptr_rec[i]); cout << endl;
            EmptyRecord(t_rec.ptr_rec[i]);
        }
    }
    
    bool read(Customers& rec) {
        
        char read_name[21];
        EmptyRecord(rec);
        cout << " Enter User name: "; read(read_name, 21);
        if (strLen(read_name) <= 0) {
            EmptyRecord(rec);
            return false;
        }
        strcpy(rec.user_name, read_name);
        cout << " Enter likes_count: "; cin >> rec.likes_count;
        cout << " Enter retweets_count: "; cin >> rec.retweets_count; 
        cout << " Enter replies_count: "; cin >> rec.replies_count; 
        cout << " Enter share videos (y/n): "; cin >> rec.share_videos; 
        return true;
    }
}
