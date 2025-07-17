// HTTPWebserver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<sstream>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include<string>
#include<vector>
#include "Email.h"
using namespace std;

int main()
{
	std::vector<Email> users
    {
        Email("JobsS",EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting on finance")),
        Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")),
        Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")),
        Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?"))
    };
    
	//starts Winsock DLLs		
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SvrAddr.sin_port = htons(8080);
	int SvrAddrlen = sizeof(SvrAddr);

	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	//listen on a socket
	if (listen(ServerSocket, 20) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	while (true)
	{
		//accepts a connection from a client
		SOCKET ConnectionSocket;
		ConnectionSocket = SOCKET_ERROR;
		if ((ConnectionSocket = accept(ServerSocket, (struct sockaddr*)&SvrAddr, &SvrAddrlen)) == SOCKET_ERROR) {
			closesocket(ServerSocket);
			WSACleanup();
			return 0;
		}

        char RxBuffer[128] = {};
        recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
		std::string webStuff = RxBuffer;
		std::string username{};

        // Extract username from the URL
        size_t usernamePos = webStuff.find("GET /?username=");
        if (usernamePos != std::string::npos) {
			const int sizeOfBadInfo{15};

            username = webStuff.substr(usernamePos + sizeOfBadInfo); // 15 is the length of "GET /?username="
            size_t spacePos = username.find(" "); // because it goes username=[username] HTTP...
            if (spacePos != std::string::npos) {
                username = username.substr(0, spacePos);
            }
        }
		
		cout << "Connection Established" << std::endl;

		std::string ServerMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
		std::string response =R"(<!DOCTYPE html>
        <html lang="en">
        <head>
            <style>
				body {
					background: lightsteelblue;
				}

				h1 {
					text-align: center;
				}
				table {
					border: 1px solid black;
					border-collapse: collapse;
					margin: 0 auto;
				}
				th, td {
					border: 1px solid black;
					padding: 20px;
				}
				th {
					background-color: lightgreen; /* Light green background for headers */
				}
				td {
					background-color: lightgray; /* Gray background for non-first cells */
				}
            </style>
        </head>
        <body>
            <h1>Emails</h1>
            <table>
                <tbody>
                <tr>
                    <th>From</th>
                    <th>To</th>
                    <th>Subject</th>
                    <th>Body</th>
                </tr>)";

        
        for(int i = 0; i < users.size(); ++i)
        {
            if(users[i].getUser() == username)
            {
                response.append("<tr><td>" 
                + users[i].getFrom() 
                + "</td><td>" 
                + users[i].getTo() 
                + "</td><td>"
                + users[i].getSubject() 
                + "</td><td>"
                + users[i].getBody() 
                + "</td></tr>");
            }
        }

        response.append("</tbody> </table> </body> </html>");

		ServerMessage.append(std::to_string(response.size()));
		ServerMessage.append("\n\n");
		ServerMessage.append(response);
	

		int bytesSent = 0;
		int totalbytesSent = 0;

		while (totalbytesSent < sizeof(ServerMessage))
		{
			bytesSent = send(ConnectionSocket, ServerMessage.c_str(), ServerMessage.size(), 0);
			if (bytesSent < 0)
			{
				std::cout << "could not send response";
			}
			totalbytesSent += bytesSent;
		}

		std::cout << "sent response to client"<<std::endl;

		closesocket(ConnectionSocket);	//closes incoming socket
	}
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources
}