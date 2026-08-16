#include "address.hpp"
#include "Ticket.hpp"
#include "logger.hpp"
#include "socket.hpp"
#include "fifo.hpp"

#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <string>
#include <array>

bool serverIsRunning {true};
int main() {
    constexpr const char* ticketsDB { "tickets.db" };
    constexpr const char* serverLog { "server.log" };

    mz::setConfiguration(mz::LogLevel::DEBUG);
    mz::setLogFile(serverLog);
    mz::logHeader();

    std::cout << "Starting Server\n";
    AS2::InetAddress addr{"127.0.0.1", 8080};
    AS2::Listener<AS2::InetAddress> server(addr);
    std::cout << "TCP server listening at 127.0.0.1:8080\n";

    const auto signalHandler = [](int signal) -> void {
        mz::info("[SIGNAL HANDLER] handling signal: " + std::to_string(signal));
        switch(signal) {
            case SIGINT:
                mz::debug("[SIGNAL HANDLER] SIGINT receieved");
                serverIsRunning = false;
                break;
            case SIGTSTP:
                mz::debug("[SIGNAL HANDLER] SIGTSTP receieved");
                serverIsRunning = false;
                break;
            case SIGPIPE:
                mz::debug("[SIGNAL HANDLER] SIGPIPE received");
                break;
            default:
                mz::warn("[SIGNAL HANDLER]: Undefined Signal");
                std::cout << "undefined signal";
        }
    };

    // Setup Signals
    struct sigaction action {};
    action.sa_handler = signalHandler;

    sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

    auto safe_sigaction = [&action](int __sig, const char* prefix, struct sigaction* old = NULL) {
		if(sigaction(__sig, &action, old) == -1) {
			std::cerr << "[Sigaction]: " << prefix << "\n";
			std::exit(1);
		}
	};

    safe_sigaction(SIGINT,  "SIGINT ");
	safe_sigaction(SIGTSTP, "SIGTSTP");
    safe_sigaction(SIGPIPE, "SIGPIPE");

    // std::vector<std::thread> threads{};
    std::cout << "waiting for client connection\n";
    // AS2::Connection<AS2::InetAddress> conn = server.accept();
    
    std::vector<AS2::Connection<AS2::InetAddress>> clients {};
    std::vector<AS2::Ticket> tickets {};
    // std::vector<AS2::Fifo> fifos {};

    std::unordered_map<std::string, AS2::Fifo> fifos{};

    int totalNumberOfClients {};
    int totalNumberOfTickets {};

    const std::string mainTicketFIFO { "/tmp/ticket_notifications.fifo" };
    ::unlink(mainTicketFIFO.data());

    fifos.try_emplace(mainTicketFIFO, mainTicketFIFO.c_str(), O_WRONLY);
    

    std::filesystem::path filePath { ticketsDB };
    if(std::filesystem::exists(filePath)) {
        std::string line;

        std::ifstream file { ticketsDB };
        while(std::getline(file, line)) {
            AS2::Ticket ticket;
            ticket.parseFullTicketString(line);
           
            if(!fifos.contains(ticket.get_fifo_name())) {
                fifos.try_emplace(ticket.get_fifo_name(), ticket.get_fifo_name().c_str(), O_RDWR);
            }
            
            fifos[mainTicketFIFO].write(ticket.get_fifo_name());
            
            ++totalNumberOfTickets;
            tickets.push_back(std::move(ticket));

            // tickets.emplace_back(line);
        }

    }

    
    // fifos.emplace_back("/tmp/ticket_notifications", O_WRONLY);
    // fifos[mainTicketFIFO] = std::move(AS2::Fifo(mainTicketFIFO.data(), O_WRONLY));

    while(serverIsRunning) {
        fd_set readSet{};
        FD_ZERO(&readSet);

        FD_SET(STDIN_FILENO, &readSet);
        int maxFd = STDIN_FILENO;

        FD_SET(server.fd(), &readSet);
        maxFd = std::max(maxFd, server.fd());

        for(const auto& client : clients) {
            FD_SET(client.fd(), &readSet);
            maxFd = std::max(maxFd, client.fd());
        }

        int ready = ::select(maxFd + 1, &readSet, nullptr, nullptr, nullptr);
        if (ready < 0) {
            std::cerr << "select()\n";
            mz::warn("[MAIN]: select() failed\n");

            break;
        }

        if (FD_ISSET(STDIN_FILENO, &readSet)) {
            std::string command;

            std::getline(std::cin >> std::ws, command);
            std::cout << "Server command: " << command << '\n';

            if (command == "quit") {
                serverIsRunning = false;
            } else if (command == "show") {
                
                std::cout << "Showing All Tickets\n";
                for(const AS2::Ticket& ticket : tickets) {
                    std::cout << ticket << "\n\n";
                }

            } else if (command == "stats") {
                
                std::cout << "\nTotal number of Clients: " << totalNumberOfClients
                    << "\nNumber of Open Clients: " << clients.size() 
                    << "\nNumber of Closed Clients: " << totalNumberOfClients - clients.size()
                    << "\n\n";

            } else if (command == "save") {
                std::cout << "Saving Tickets to " << ticketsDB << "\n";

                std::ofstream ofstr(ticketsDB);
                for(auto iter = tickets.begin(); iter < tickets.end(); ++iter) {
                    ofstr << iter->to_raw_string() << "\n";
                }

                std::cout << "Successfully Saved Tickets to " << ticketsDB << "\n\n";

            } else if (command == "clients") {
                
                std::cout << "Number of Connected Clients: " << clients.size() << "\n\n";
            
            } else {
            
                std::cout << "[ERROR]: Command not recongized.\n "
                    << "Please choose (quit, stats, save, clients, show)\n\n";
            
            }

        }

        if (FD_ISSET(server.fd(), &readSet)) {
            std::cout << "Accepting client...\n";

            ++totalNumberOfClients;
            clients.push_back(server.accept());
        }

        for (auto it = clients.begin(); it != clients.end(); ) {
            if (FD_ISSET(it->fd(), &readSet)) {
                std::string input = it->read_all();

                mz::debug("[MAIN]: recieved input: " + input);
                std::cout << "Received: " << input << '\n';

                if (input.empty()) {
                 
                    std::cout << "Client disconnected\n";
                    it = clients.erase(it);
                 
                    --totalNumberOfClients;
                    continue;

                } else if (input.starts_with("submit")) {
                    
                    AS2::Ticket ticket;
                    try {
                        ticket.parseTicketString(input);
                        tickets.push_back(ticket);
                        ++totalNumberOfTickets;

                        // Add the current user to the fifo if needed
                        const std::string ticketFIFOName { "/tmp/ticket_notifications_" + ticket.get_name() + ".fifo" };
                        if(!fifos.contains(ticketFIFOName)) {
                            fifos.try_emplace(ticketFIFOName, ticketFIFOName.c_str(), O_RDWR);
                            fifos[mainTicketFIFO].write(ticketFIFOName);
                            // fifos[ticket.get_name()] = std::move(AS2::Fifo(ticketFIFOName.data(), O_WRONLY));
                        }

                        // Notify the fifo that [username] wrote to it
                        const std::string ticketFIFOMessage { 
                            "[NOTIFY] Ticket " + std::to_string(ticket.id()) 
                            + " created by " + ticket.get_name() + ", priority: " 
                            + AS2::to_string(ticket.getPriority()) 
                        };

                        if(!fifos[ticketFIFOName].write(ticketFIFOMessage)) {
                            // Failed to write to FIFO for some reason
                            std::cerr << "[ERROR] Failed to write to FIFO for: " << ticket.get_name() << "\n"; 
                            mz::warn("[Main]: Failed to write to FIFO: " + ticketFIFOName);
                        }

                        std::cout << "Successfully Wrote to FIFO\nSuccessfully Added Ticket\n";   
                        input = "Successfully Added Ticket";                 
                    } catch(const std::runtime_error& e) { input = e.what(); }

                } else if (input.starts_with("list")) {
                    
                    const std::string statusStr { input.substr(input.find_first_of("|") + 1) };
                    mz::debug("[MAIN]: Status: " + statusStr);

                    if(statusStr == "all") {
                        for(const AS2::Ticket& ticket : tickets) {
                            input += ticket.to_string() + "\n\n";
                        }
                    } else {
                        const AS2::Status status = AS2::status_from_string(statusStr);
                        for(const AS2::Ticket& ticket : tickets) {
                            if(ticket.getStatus() != status) continue;
                            input += ticket.to_string() + "\n\n";
                        }
                    }

                } else if (input.starts_with("detail")) {
                    
                    const std::string detailID { input.substr(input.find_first_of("|") + 1) };
                    try {
                        const size_t ID { std::stoull(detailID) };
                        const auto iter { std::find_if(tickets.begin(), tickets.end(), [&ID](const AS2::Ticket& t) {return t.id() == ID;}) };

                        if(iter == tickets.end()) { input = "Ticket doesn't exist"; } 
                        else { input = iter->to_string(); }

                    } catch (const std::invalid_argument& e) {input = e.what();}
                
                } else if (input.starts_with("close")) {
                    
                    const std::string detailID { input.substr(input.find_first_of("|") + 1) };
                    try {
                        const size_t ID { std::stoull(detailID) };
                        const auto iter { std::find_if(tickets.begin(), tickets.end(), [&ID](const AS2::Ticket& t) {return t.id() == ID;}) };

                        if(iter == tickets.end()) { input = "Ticket doesn't exist"; } 
                        else {
                            const std::string ticketFIFOMessage { "[NOTIFY] Ticket " + std::to_string(iter->id()) + " closed" };
                            if(!fifos[iter->get_fifo_name()].write(ticketFIFOMessage)) {
                                // Failed to write to FIFO for some reason
                                std::cerr << "[ERROR] Failed to write to FIFO for: " << iter->get_name() << "\n"; 
                                mz::warn("[Main]: Failed to write to FIFO");
                            }

                            iter->close(); 
                            input = "Ticket Closed";
                        }

                    } catch (const std::invalid_argument& e) {input = e.what();}
                } else if (input.starts_with("stats")) {
                    input = "Total number of Tickets opened: " + std::to_string(totalNumberOfTickets)
                        + "\nTotal number of Open Tickets: " + std::to_string(tickets.size())
                        + "\nNumber of Closed Tickets: " + std::to_string(totalNumberOfTickets - tickets.size())
                        + "\n";
                }

                it->write_all("Server: " + input);
            }

            ++it;
        }
    }

    std::cout << "Cleaning up Server\n";
    fifos[mainTicketFIFO].write("[NOTIFY] Server Shutting Down");
    for(auto& [path, ticket] : fifos) {
        ticket.cleanup();
        ::unlink(path.c_str());
    }

    return 0;
}