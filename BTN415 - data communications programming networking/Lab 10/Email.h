#pragma once
#include <string>

struct EmailDetails
{
    std::string from;
    std::string to;
    std::string subject;
    std::string body;
    EmailDetails() = default;
    EmailDetails(const std::string& from, const std::string& to, const std::string& subject, const std::string& body);
};

class Email
{
public:
    Email();
    Email(const std::string& userName, const EmailDetails& details);
    const std::string display();
    const std::string getUser();
    const std::string getFrom() const;
    const std::string getTo() const;
    const std::string getSubject() const;
    const std::string getBody() const;
    const EmailDetails getDetails();
private:
    std::string userName;
    struct EmailDetails details;
};