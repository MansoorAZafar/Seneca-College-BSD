// serialServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "socket.h"

int main() {
    std::string message = "Hello";
    packet my_packet, recovered_packet;
    my_packet = create_packet();

    struct serialized_packet serialized_data = packet_serializer(my_packet);

    Server_TCP server("127.0.0.1", 27000);

    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();
    std::cout << "Waiting for a client to connect." << std::endl;
    server.accept_connection();

    server.send_packet(my_packet);
    server.receive_message(message);
    std::cout << "Message Received: " << message << std::endl;

    return 0;
}
