#include <iostream>
#include <string>
#include "socket.h"

int main() {
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;

    Client_TCP client;
    client.create_socket();
    client.connect_socket("127.0.0.1", 27000);

    // Send the username
    client.send_message(username);

    // Receive packet
    packet dataPacket;
    client.receive_packet(dataPacket);

    // Deserialize and display emails
    // Deserialize and display emails
    std::cout << "Received emails:\n" << dataPacket.size << std::endl;

    std::cout << "Received emails:\n" << dataPacket.letters << std::endl;

    return 0;
}
