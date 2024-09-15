// Name : Mansoor Zafar 
// Date : 2024-02-02
// ID   : 100503226
// BTN415 NCC Lab 1

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Could not start DLLs" << std::endl;
        return 0;
    }

    SOCKET ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(27000);
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr))) == SOCKET_ERROR) {
        std::cout << "Failed to connect" << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

    char TxBuffer[128] = {};
    std::cout << "Enter a weight in lbs\n> ";
    std::cin >> TxBuffer;
    send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);

    char RxBuffer[128] = {};
    recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
    std::cout << "Response\n> " << RxBuffer << std::endl;

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}





