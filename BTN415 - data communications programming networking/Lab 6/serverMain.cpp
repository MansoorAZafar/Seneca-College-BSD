#include <iostream>
#include <string>
#include <vector>
#include "Sockets.h"
#include "Email.h"
 
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
    Server_TCP server("127.0.0.1", 28000);

    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();
    std::cout << "Waiting for Conenctions. " << std::endl;
    server.accept_connection();
    std::cout << "Connection accepted. " << std::endl;
    server.receive_message(username);

    std::cout << "Username Received: " << username << std::endl;
    std::string ack{};
    for(int i = 0; i < users.size(); ++i)
    {
        if(users[i].getUser() == username)
        {
            server.send_message(users[i].display());
            server.receive_message(ack);
        }
    }

    

    return 0;
}