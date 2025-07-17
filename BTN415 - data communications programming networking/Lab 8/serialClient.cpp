// serialClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "Email.h"
#include "socket.h"

std::string getUsername()
{
    std::string username{};
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    return username;
}

int main() {
    
    std::string username = getUsername();
    
    std::string message = "Hello";
    packet recovered_packet;

    Client_TCP client;
    client.create_socket();
    client.connect_socket("127.0.0.1", 27000);

    //Sending the username as a char array
    client.send_message(username);
    
    std::cout << "Displaying the email message:\n" << std::setw(60) << std::setfill('*') << "\n" << std::setfill(' ');
    while(client.receive_packet(recovered_packet))
    {
        std::cout << "From: " << recovered_packet.from << "\n"
        << "To: " << recovered_packet.to << "\nSubject: " << recovered_packet.subject << 
        "\nBody: " << recovered_packet.body  << "\n"
        << std::setw(60) << std::setfill('*') << " \n" << std::setfill(' ');
        //std::cout << message << std::setw(60) << std::setfill('*') << " \n" << std::setfill(' ');
        client.send_message("ack");
    }


    return 0;
}