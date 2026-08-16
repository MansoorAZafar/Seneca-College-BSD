#include "logger.hpp"
#include "socket.hpp"
#include <algorithm>
#include <signal.h>
#include <iostream>
#include <string>
#include <limits>
#include <array>

void printInstructions() {
    std::cout << "***************************"
        "\nWelcome to the Ticketing System!"
        "\n\n\tHere you can submit, list, detail\n"
        "\tclose or get the stats of tickts!"
        "\n\nPlease delimit arguments with |"
        "\n\nExamples:"
        "\n\tSUBMIT|Ali|NETWORK|HIGH|Cannot access Linux VM"
        "\n\tLIST|OPEN or LIST|ALL"
        "\n\tDETAIL|3"
        "\n\tCLOSE|3"
        "\n\tSTATS"
        "\n\tQUIT"
        "\n\n***************************\n\n";
}

struct Input {
    std::string raw_input{};
    std::string lower_input{};
};

bool clientIsRunning { true };
int main() {
    mz::setConfiguration(mz::LogLevel::INFO);
    mz::setLogFile("client.log");
    mz::logHeader();

    const auto signalHandler = [](int signal) -> void {
        mz::info("[SIGNAL HANDLER] handling signal: " + std::to_string(signal));
        switch(signal) {
            case SIGINT:
                mz::debug("[SIGNAL HANDLER] SIGINT receieved");
                clientIsRunning = false;
                break;
            case SIGTSTP:
                mz::debug("[SIGNAL HANDLER] SIGTSTP receieved");
                clientIsRunning = false;
                break;
            default:
                mz::warn("[SIGNAL HANDLER]: Undefined Signal");
                std::cerr << "undefined signal";
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


    const auto getInput = [](const std::string_view& msg) -> Input {
        std::cout << msg << "\n> ";

        std::string input{};
        std::string raw_input { input };
        std::getline(std::cin >> std::ws, input);
        
        std::cout << "\n";
        std::transform(input.begin(), input.end(), input.begin(), [](const unsigned char& c){
            return std::tolower(c);
        });
        
        return { raw_input, input };
    };
    
    // Client INIT
    std::cout << "Initializing Client\n";
    AS2::InetAddress server{"127.0.0.1", 8080};
    AS2::StreamSocket client {AF_INET, SOCK_STREAM};
    
    std::cout << "Client Connecting to Server\n";
    client.connect(server);
    std::cout << "Client Successfully Connected to Server\n\n";

    while(clientIsRunning) {
        std::system("clear");

        printInstructions();
        const auto [raw_input, input] = getInput("Enter your Command:"
            "\nSUBMIT ( Creates a new Ticket      )"
            "\nLIST   ( Lists Tickets by Status   )"
            "\nDETAIL ( Displays one Ticket by ID )"
            "\nCLOSE  ( Close an Existing Ticket  )"
            "\nSTATS  ( Show Ticket Statistics    )"
            "\nQUIT   ( Disconnects this Client   )"
        );

        mz::info("[MAIN]: Client Operation: " + input);
        if(input == "quit") {
            clientIsRunning = false;
            mz::info("[Main]: Disconnecting Client");
            continue;
        } else if (
            input.starts_with("submit")
            || input.starts_with("list")
            || input.starts_with("detail")
            || input.starts_with("close")
            || input.starts_with("stats")
        ) {
            client.write_all(input);
            const std::string response { client.read_all() };
            
            std::cout << response << "\n\n"; 
        } else { std::cout << "Invalid Input\n\n"; }
 
        std::cout << "Press Enter to continue";
        std::cin.get();
    }
    
    // const std::string message { client.read_all() };

    // std::cout << "Recieved from Server: " << message << "\n";
    // client.write_all("Hello from Client");

    return 0;
}