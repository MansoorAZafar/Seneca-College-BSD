#define _CRT_SECURE_NO_WARNINGS
#include "Email.h"
#include <iostream>
#include <string>
#include <cstring>
//#define DEV_MODE 

EmailDetails::EmailDetails(const char* from, const char* to, const char* subject, const char* body)
{
    this->addAndAssign(this->from, from);
    this->addAndAssign(this->to, to);
    this->addAndAssign(this->subject, subject);
    this->addAndAssign(this->body, body);
}

EmailDetails::EmailDetails(const EmailDetails& other)
{
    this->operator=(other);
}

EmailDetails& EmailDetails::operator=(const EmailDetails& other)
{
    if (this != &other)
    {
        if (other.from && other.body && other.subject && other.to)
        {
            this->addAndAssign(this->from, other.from);
            this->addAndAssign(this->body, other.body);
            this->addAndAssign(this->subject, other.subject);
            this->addAndAssign(this->to, other.to);
        }
        else
        {
            this->body = nullptr;
            this->from = nullptr;
            this->subject = nullptr;
            this->to = nullptr;
        }
    }
    return *this;
}

EmailDetails::~EmailDetails()
{
    if (this->from) delete[] this->from;
    if (this->to) delete[] this->to;
    if (this->subject) delete[] this->subject;
    if (this->body) delete[] this->body;
}

void EmailDetails::addAndAssign(char*& des, const char* src)
{
    if (des) delete[] des;
    des = new char[std::strlen(src) + 1];
    std::strcpy(des, src);
}

Email::Email()
{

    this->userName = new char[8];
    std::strcpy(this->userName, "Default");
    this->details.addAndAssign(this->details.to, "Class");
    this->details.addAndAssign(this->details.from, "Zara");
    this->details.addAndAssign(this->details.subject, "Announcement");
    this->details.addAndAssign(this->details.body, "Welcome to BTN");
}

const std::string Email::serialize()
{
    std::string res = "From: ";
    res += this->details.from;
    res += "\nTo: ";
    res += this->details.to;
    res += "\nSubject: ";
    res += this->details.subject;
    res += "\nBody: ";
    res += this->details.body;
    res += "\n";
    return res;
}

Email::Email(const char* userName, const EmailDetails& details)
{
    this->userName = new char[std::strlen(userName) + 1];
    std::strcpy(this->userName, userName);
    this->details = details;
}

Email::~Email()
{
    if (this->userName) delete[] this->userName;
}

Email::Email(const Email& other)
{
    this->operator=(other);

#if defined(DEV_MODE)
    std::cout << "Email::Email(const Email& other) called\n";
#endif
}

Email& Email::operator=(const Email& other)
{
#if defined(DEV_MODE)
    std::cout << "Email::operator=(const Email& other) called\n";
#endif
    if (this != &other)
    {
        if (this->userName)
            delete[] this->userName;

        if (other.userName) {
            this->userName = new char[std::strlen(other.userName) + 1];
            std::strcpy(this->userName, other.userName);
        }
        else {
            this->userName = nullptr;
        }

        this->details = other.details;
    }
    return *this;
}

const char* Email::getUser()
{
    return this->userName;
}

const EmailDetails Email::getDetails()
{
    return this->details;
}

const char* Email::getFrom() const {
    return this->details.from;
}

const char* Email::getTo() const {
    return this->details.to;
}

const char* Email::getSubject() const {
    return this->details.subject;
}

const char* Email::getBody() const {
    return this->details.body;
}