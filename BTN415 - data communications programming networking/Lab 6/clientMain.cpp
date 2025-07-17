#include <iostream>
#include <string>
#include <iomanip>
#include "Sockets.h"
#include "Email.h"

std::string getUsername()
{
    std::string username{};
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    return username;
}

int main()
{
    std::string message = "Hello";
    
    Client_TCP client;
    client.create_socket();
    client.connect_socket("127.0.0.1", 28000);
    
    std::string username = getUsername();
    client.send_message(username);

    std::cout << "Displaying the email message:\n" << std::setw(60) << std::setfill('*') << "\n" << std::setfill(' ');
    while(client.receive_message(message))
    {
        std::cout << message << std::setw(60) << std::setfill('*') << " \n" << std::setfill(' ');
        client.send_message("ack");
;
    }
    client.receive_message(message);
    std::cout << "Message Received: " << message << std::endl;
}