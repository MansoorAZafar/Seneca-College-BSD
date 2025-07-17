#include "Email.h"
#include <iostream>
#include <string>

EmailDetails::EmailDetails(const std::string& from, const std::string& to, const std::string& subject,const std::string& body)
{
    this->from = from;
    this->to = to;
    this->subject = subject;
    this->body = body;
}

Email::Email()
{
	Email::userName = "Default";
	Email::details.to = "Class";
	Email::details.from = "Zara";
	Email::details.subject = "Announcement";
	Email::details.body = "Welcome to BTN";

}

std::string Email::display()
{
	return Email::details.body;
}

Email::Email(const std::string& userName, const EmailDetails& details)
{
    this->userName = userName;
    this->details = details;
}