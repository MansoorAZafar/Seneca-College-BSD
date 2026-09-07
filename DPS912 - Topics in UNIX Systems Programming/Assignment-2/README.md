# Designs
## Socket Choice
TCP. I chose TCP as the socket choice as for a ticketing system that is meant to be used from numerous different teachers and students, it is unreasonable to have them all work on the same machine. Rather, it makes sense that many different teachers and students should be able to use the client from anywhere to make a ticket, not limited a specific machine. As such, the entire AF_UNIX domain is ruled out, as a ticketing system made for numerous students and teachers should not be limited to a specific machine rather, should be available across multiple machines. For example, matrix is not limited to a specific machine, rather, we use some software to access matrix on our own devices, not needing to use 1 specific device. Then the decision for TCP vs UDP, I chose TCP as UDP is needed when performance is critical, the loss of packets is acceptable and not needed in order however, for a ticketing system, we want to ensure we get all tickets and requests. We don't want to drop tickets or have them corrupted and want to ensure we get processes in order. We cannot have something like, cancel ticket 2 before ticket 2 is even made. As such, I went for a TCP socket.

## Project Structure
```
├── Makefile
├── README.md
├── core
│   ├── address.cpp
│   └── socket.cpp
├── dependencies
│   └── logger.hpp
├── include
│   ├── address.hpp
│   ├── fifo.hpp
│   └── socket.hpp
├── sample-output
│   ├── client.txt
│   ├── monitor.txt
│   └── server.txt
├── screenshots
│   ├── 1. Server Starting.png
│   ├── 2. Monitor starts and waits.png
│   ├── 3. 2 clients join.png
│   ├── 4. Both clients submit a ticket.png
│   ├── 5 Client Lists OPEN tickets.png
│   ├── 6. Ticket Closed.png
│   ├── 7. Server Rejects Command.png
│   ├── 8. Server Commands.png
│   ├── 8.1 Server Commands V2.png
│   └── 9. Closing Server via Ctrl +C.png
├── src
│   ├── Ticket.cpp
│   ├── Ticket.hpp
│   ├── ticketClient.cpp
│   ├── ticketMonitor.cpp
│   └── ticketServer.cpp
└── tickets.db
```

### Dependencies/logger
A header only logger file made by me. It's a thread-safe Queue based logger using the producer consumer pattern.


## FIFO Design

Rather than making extra FIFO's I chose to make a main server FIFO which will hold all the dynamic user FIFOs. So the monitor will first connect with the server fifo, we'll call this SF. Then when a client connects, a new FIFO is made with the the postfix of the clients name. I.e. ticket_notifications_bob.fifo. The client FIFO is made on the server and then if this is a newly made FIFO, SF (Server FIFO) will write to the monitor the name of the newly made client FIFO. The monitor will read this name and connect to that FIFO as read only. The server when making the client FIFO will make it with both read and write permissions as the monitor cannot start reading until it knows about the FIFO. That is to say:

a new client submits a request
-> server sees this is a NEW client
-> server makes a NEW FIFO with the client name as the postifx
-> server makes the FIFO with read AND write permissions
-> Since the newly made FIFO isn't waiting for a reader, the server can now write to monitor the FIFO
-> Server writes to monitor the new FIFO
-> monitor reads the FIFO
-> monitor connects to the FIFO with read only




# Research and Out-of-the-Box Questions
1. IPC Selection in Industry
	
	Any financial trading platform would use this kind of architecture of sockets for request/response and FIFOs for notifications. As they get loads of notifications, they offload the notifications to something like Kafka. 
	
2. Reliability
	When ticketMonitoring ins't running, the server will constantly be waiting for the monitor to connect to its original FIFO. The server would be stuck waiting infinitely. A production system could avoid losing data by passing all that data into some log file or regualr file. Or they could use some backup connection to try and write to that. 
	
3. Security
	Anyone can read and write to tmp, which could read and or write to the fifos. Due to this, could potentially perform DOS by flooding the FIFOs constantly or resource leakage by keeping a reference open to it. Also, attackers could create the FIFO before hand with the exact same name and get the servers to read whatever they put in before hand.
	
4. Event Streaming Trend
	Similarly to other streaming services, our FIFO notification channel allows for our producer (server) to send events to then be consumed by consumer (monitor). Where the producer and consumer are completely separate and decoupled, where neither are waiting in an infinte loop with busy waiting, just like streaming services. However, as we are using FIFO, our implementation is bound to the current machine and not across different machines like other streaming services do. Furthermore, our monitor doesn't persist messages, it just consumes and prints them, not storing them. 
