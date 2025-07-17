// UDPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Name : Mansoor Zafar 
// Date : 2024-02-16
// ID   : 100503226
// BTN415 NCC Lab 4


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

    SOCKET ServerSocket;
    ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ServerSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = INADDR_ANY;
    SvrAddr.sin_port = htons(27020);
    if (bind(ServerSocket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr)) == SOCKET_ERROR) {
        std::cout << "Could not bind socket to port" << std::endl;
        closesocket(ServerSocket);
        WSACleanup();
        return 0;
    }
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while(true)
    {
        char RxBuffer[128] = {};
        struct sockaddr_in CltAddr;
        int addr_len = sizeof(CltAddr);
        recvfrom(ServerSocket, RxBuffer, sizeof(RxBuffer), 0,
            (struct sockaddr*)&CltAddr, &addr_len);
        if(RxBuffer[0] == '\0') break;
        sendto(ServerSocket, "Ack", sizeof("Ack"), 0,
            (struct sockaddr*)&CltAddr, sizeof(CltAddr));
    }
    end = std::chrono::system_clock::now();
    const auto nanos = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "It took " << nanos.count() << " milliseconds to send \"no\" 100_000 times for the UDP Server\n";

    closesocket(ServerSocket);
    WSACleanup();

    return 0;
}