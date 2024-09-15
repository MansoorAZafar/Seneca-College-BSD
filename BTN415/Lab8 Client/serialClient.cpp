// serialClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "socket.h"

int main() {
    std::string message = "Hello";
    packet recovered_packet;

    Client_TCP client;
    client.create_socket();
    client.connect_socket("127.0.0.1", 27000);

    client.receive_packet(recovered_packet);
    std::cout << "Packet name: " << recovered_packet.name << std::endl;
    std::cout << "Packet flag: " << recovered_packet.flag << std::endl;
    std::cout << "Packet size: " << recovered_packet.size << std::endl;
    for (int i = 0; i < recovered_packet.size; i++) {
        std::cout << "Packet letter: " << i << " " << recovered_packet.letters[i] << std::endl;
    }
    client.send_message("Got your message!");

    return 0;
}
