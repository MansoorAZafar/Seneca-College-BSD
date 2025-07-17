// UDPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Name : Mansoor Zafar 
// Date : 2024-02-16
// ID   : 100503226
// BTN415 NCC Lab 4


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <chrono>
#pragma comment(lib, "Ws2_32.lib")

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Could not start DLLs" << std::endl;
        return 0;
    }

    SOCKET ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(27020);
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int cnt{};
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while(cnt < 100000)
    {
        char TxBuffer[128] = {"no"};
        sendto(ClientSocket, TxBuffer, sizeof(TxBuffer), 0,
        (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));

        char RxBuffer[128] = {};
        int addr_len = sizeof(SvrAddr);
        recvfrom(ClientSocket, RxBuffer, sizeof(RxBuffer), 0,
        (struct sockaddr*)&SvrAddr, &addr_len);
        ++cnt;
    }
    end = std::chrono::system_clock::now();
    const auto nanos = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "It took " << nanos.count() << " milliseconds to send \"no\" 100_000 times for the UDP Client\n";
    

    closesocket(ClientSocket);
    WSACleanup();
}

