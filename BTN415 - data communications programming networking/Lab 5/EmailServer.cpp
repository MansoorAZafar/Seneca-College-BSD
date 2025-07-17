// EmailServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <winsock2.h>


#include "Email.h"
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    std::vector<Email> user{
        Email("JobsS",EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting on finance")), Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")), Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")), Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?"))
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
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}
	

	cout << "Waiting for client connection\n" << endl;

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	cout << "Connection Established" << endl;
	
	//receives RxBuffer
	char RxBuffer[sizeof(Email)] = {};
	recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	Email *em = reinterpret_cast<Email*>(RxBuffer);
	std::cout <<"Displaying the email message:  "<<em->display() << endl;
	//send(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	
	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources
}