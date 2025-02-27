#pragma once
#include <string>

struct EmailDetails
{
    char* from{};
    char* to{};
    char* subject{};
    char* body{};
    EmailDetails() = default;
    EmailDetails(const char* from, const char* to, const char* subject, const char* body);
    EmailDetails(const EmailDetails& other);
    EmailDetails& operator=(const EmailDetails& other);
    ~EmailDetails();
    static void addAndAssign(char*& des, const char* src);

};



class Email
{
public:
    Email();
    Email(const char* userName, const EmailDetails& details);
    ~Email();
    Email(const Email& other);
    Email& operator=(const Email& other);
    const std::string serialize();
    const char* getUser();
    const EmailDetails getDetails();
private:
    char* userName{};
    struct EmailDetails details;
};