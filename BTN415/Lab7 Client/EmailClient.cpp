// EmailClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "Email.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}

	std::string username{};
	std::cout << "Enter username: ";
	std::getline(std::cin, username);



	//receives Rxbuffer


	//sends Txbuffer
	std::cout << "Sending Username to server" << endl;
	char TxBuffer[128]{};
	send(ClientSocket, username.c_str(), 128, 0);
	std::cout << "Waiting for response!\n\n";


	
	std::cout << std::setw(60) << std::setfill('*') << "\n" << std::setfill(' ');
	while (true)
	{
		char RxBuffer[128]{};
		recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
		if (RxBuffer[0] == 'D') break;
		std::string msg{ RxBuffer };
		std::cout << "Displaying the email message:  \n" << msg << endl;
		send(ClientSocket, "ack", sizeof("ack"), 0);
		std::cout << std::setw(60) << std::setfill('*') << "\n" << std::setfill(' ');
	}
	


	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();
}