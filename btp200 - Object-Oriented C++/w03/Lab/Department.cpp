#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Department.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | January 19, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

using namespace std;

namespace sdds {


    //fully provided for students to display details of a project
    void display(const Project& project) {
        cout << "Project " << project.m_topic
            << " will cost a total of " << project.m_cost << " C$." << endl;
    }

    //fully provided for students to display details of a department
    void display(const Department& department) {
        Project* temp = department.fetchProjects();
        int projects = department.fetchNumProjects();
        cout << "Department " << department.fetchName() << " details:" << endl;
        cout << "Budget: " << department.fetchBudget()
            << " and the number of projects in progress is: " << projects << endl;
        cout << "Below are the details of the projects we are currently working on: " << endl;
        for (int i = 0; i < projects; i++) {
            display(temp[i]);
        }
    }

    void Department::updateName(const char* newname) {
        auto len = strlen(newname);
        if (len > 0) {
            delete[] this->dep_name;
            this->dep_name = nullptr;
            this->dep_name = new char[len + 1];
            strcpy(this->dep_name, newname);
        }
    }
    void Department::updateBudget(double change) {
        this->budget += change;
    }
    bool Department::addProject(Project& newproject) {
        if (this->remainingBudget() > newproject.m_cost) {
            int size = this->noOfProj + 1;
            Project* tmp = new Project[size];
            for (int i = 0; i < this->noOfProj; i++) {
                tmp[i] = this->pro_rec[i];
            }
            tmp[this->noOfProj] = newproject;
            delete[] this->pro_rec;
            this->pro_rec = tmp;
            this->noOfProj = size;
            return true;
        }
        return false;
    }
    void Department::createDepartment(const char* newname,
        Project& newproject,
        double change) {
        this->updateName(newname);
        this->addProject(newproject);
        this->updateBudget(change);
    }
    Project* Department::fetchProjects() const {
        return this->pro_rec;
    }
    int Department::fetchNumProjects() const {
        return this->noOfProj;
    }
    double Department::fetchBudget() const {
        return this->budget;
    }
    char* Department::fetchName() const {
        return this->dep_name;
    }
    double Department::totalexpenses() {
        double total = 0;
        for (int i = 0; i < this->noOfProj; i++) {
            total += this->pro_rec[i].m_cost;
        }
        return total;
    }
    double Department::remainingBudget() {
        double value = this->fetchBudget();
        for (int i = 0; i < this->noOfProj; i++) {
            value -= this->pro_rec[i].m_cost;
        }
        return value;
    }
    void Department::clearDepartment() {
        for (int i = 0; i < this->noOfProj; i++) {
            delete[] this->dep_name;
            this->dep_name = nullptr;
        }
        delete[] this->pro_rec;
        //delete[] this;
    }

}