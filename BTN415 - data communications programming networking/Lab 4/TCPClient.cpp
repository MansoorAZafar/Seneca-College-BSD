// Name : Mansoor Zafar 
// Date : 2024-02-16
// ID   : 100503226
// BTN415 NCC Lab 4

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include <windows.networking.sockets.h>
#include <winsock2.h>
#include <chrono>
#pragma comment(lib, "ws2_32")

#include <iostream>
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

	//receives Rxbuffer
    int cnt{};
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
	while (cnt < 100000) {
		//sends Txbuffer		
		char TxBuffer[128] = {"no"};
		send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
		char RxBuffer[128] = {};
        recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
        ++cnt;
	}
    end = std::chrono::system_clock::now();
    const auto nanos = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "It took " << nanos.count() << " milliseconds to send \"no\" 100_000 times for the TCP Client\n";

	//frees Winsock DLL resources
	closesocket(ClientSocket);
    WSACleanup();
}