#include <iostream>
#include <string>
#include <iomanip>
#include "Sockets.h"
#include "Email.h"

void display(unsigned char bitregister) {
    for (int k = 0; k < 8; k++) {
        //always outputs the rightmost bit
        std::cout << (int)(bitregister >> 7);
        bitregister = bitregister << 1;
    }
    std::cout << std::endl;
}

std::string getUsername()
{
    std::string username{};
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    return username;
}

unsigned char calcCheckSum(const std::string& str) {
    unsigned char checksum{0};
    for(const char& ch: str) {
        unsigned char var2 = (ch << 1) + ( ((ch & 0x80) >> 7) ^
                                           ((ch & 0x20) >> 5) ^
                                           ((ch & 0x04) >> 2));
        checksum ^= var2;
    }
    return checksum;
}

int main()
{
    std::string message = "Hello";
    
    Client_TCP client;
    client.create_socket();
    client.connect_socket("127.0.0.1", 28000);
    
    std::string username = getUsername();
    unsigned char checksum = calcCheckSum(username);
    std::cout << "Sending CheckSum: ";
    display(checksum);
    std::cout << "\n";

    client.send_message(username);
    client.send_message(std::to_string(checksum));




    std::cout << "Displaying the email message:\n" << std::setw(60) << std::setfill('*') << "\n" << std::setfill(' ');
    while(client.receive_message(message))
    {
        client.send_message("ack");
        
        
        std::string recChecksumStr{};
        client.receive_message(recChecksumStr);
        unsigned char recievedChecksum{static_cast<unsigned char>(std::atoi(recChecksumStr.c_str()))};
        std::string str{message.substr(message.size() - 5, message.size())};
        checksum = calcCheckSum(str);

        if(checksum != recievedChecksum) {
            std::cout << "data is corrupted\n";
            return 0;
        }
        
        std::cout << "Server Checksum: ";
        display(checksum);
        std::cout << "Client Checksum: ";
        display(checksum);
        std::cout << "\n";


        std::cout << message << std::setw(60) << std::setfill('*') << " \n" << std::setfill(' ');
        client.send_message("ack");
;
    }
    client.receive_message(message);
    std::cout << "Message Received: " << message << std::endl;
}