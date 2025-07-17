// serialServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "Email.h"
#include "socket.h"

int main() {
    std::vector<Email> users
    {
        Email("JobsS",EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting on finance")),
        Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")),
        Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")),
        Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?"))
    };
    std::string message = "Hello";
    packet recovered_packet;

    Server_TCP server("127.0.0.1", 27000);

    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();
    std::cout << "Waiting for a client to connect." << std::endl;
    server.accept_connection();

    std::string username{};
    std::string ack{};
    if(!server.receive_message(username)) return 0;

    for(unsigned int i = 0u; i < users.size(); ++i) {
        if(users[i].getUser() == username) {
            //serialize this data in the form of a packet and send this back to the Client.
            packet my_packet;
            my_packet = create_packet(users[i].serialize());

            server.send_packet(my_packet);
            server.receive_message(ack);
        }
    }

    return 0;
}