#include <iostream>
#include <string>
#include <vector>
#include "Sockets.h"
#include "Email.h"
 
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

void display(unsigned char bitregister) {
    for (int k = 0; k < 8; k++) {
        //always outputs the rightmost bit
        std::cout << (int)(bitregister >> 7);
        bitregister = bitregister << 1;
    }
    std::cout << std::endl;
}

int main() 
{
    std::vector<Email> users
    {
        Email("JobsS",EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting on finance")),
        Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")),
        Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")),
        Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?"))
    };

    std::string username = "";
    std::string recChecksumStr{};
    Server_TCP server("127.0.0.1", 28000);

    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();
    std::cout << "Waiting for Conenctions. " << std::endl;
    server.accept_connection();
    std::cout << "Connection accepted. " << std::endl;
    server.receive_message(username);
    server.receive_message(recChecksumStr);
    unsigned char recievedChecksum{static_cast<unsigned char>(std::atoi(recChecksumStr.c_str()))};
    std::cout << "Username Received: " << username << "\n\n";
    
    auto checkSum = calcCheckSum(username);
    std::cout << "Server checksum: ";
    display(checkSum);

    std::cout << "Client checksum: ";
    display(recievedChecksum);
    std::cout << "\n";
    
    if(checkSum != recievedChecksum) {
        std::cout << "Data was corrupted\n";
        return 0;
    }
    
    std::string ack{};
    for(int i = 0; i < users.size(); ++i)
    {
        if(users[i].getUser() == username)
        {
            server.send_message(users[i].display());
            server.receive_message(ack);
            
            std::string str = {users[i].display().substr(users[i].display().size() - 5, users[i].display().size())};
            checkSum = calcCheckSum(str);
            std::cout << "Sending Checksum: ";
            display(checkSum);
            server.send_message(std::to_string(checkSum));

            server.receive_message(ack);
        }
    }

    

    return 0;
}