#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "socket.h"
#include "Email.h"

int main() {
    std::vector<Email> users
    {
        Email("JobsS", EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting on finance")),
        Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")),
        Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")),
        Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?"))
    };

    Server_TCP server("127.0.0.1", 27000);
    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();

    std::cout << "Waiting for a client to connect." << std::endl;
    server.accept_connection();

    // Receive username
    std::string username;
    server.receive_message(username);

    // Search for emails corresponding to the provided username
    std::string serializedData;
    for (size_t i = 0u; i < users.size(); ++i) {
        if (users[i].getUser() == username) {
            serializedData += users[i].serialize() + "\n";
        }
    }

    // Create a packet and send it back to the client
    packet dataPacket;
    std::strcpy(dataPacket.name, "EmailData");
    dataPacket.flag = true; // Assuming the data is larger than 10 characters
    dataPacket.size = serializedData.size();
    dataPacket.letters = new char[dataPacket.size + 1];
    std::strcpy(dataPacket.letters, serializedData.c_str());
    std::cout << "sending : " << dataPacket.letters << "\n";
    server.send_packet(dataPacket);
    // After sending the packet
    delete[] dataPacket.letters; // Free the memory allocated for the letters array

    return 0;
}
