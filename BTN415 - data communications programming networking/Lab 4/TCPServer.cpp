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

    SOCKET ListenSocket;
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    SvrAddr.sin_port = htons(27000);
    if (bind(ListenSocket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr)) == SOCKET_ERROR) {
        std::cout << "Could not bind socket to port" << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

    if (listen(ListenSocket, 3) == SOCKET_ERROR) {
        std::cout << "Could not start to listen" << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

    SOCKET ClientSocket;
    
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Failed to accept connection" << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

    closesocket(ListenSocket);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while(true)
    {
        char RxBuffer[128] = {};
        recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
        if(RxBuffer[0] == '\0') break;
        char TxBuffer[128]{"Ack"};
        send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
    }
    end = std::chrono::system_clock::now();
    const auto nanos = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "It took " << nanos.count() << " milliseconds to send \"no\" 100_000 times for the TCP Server\n";

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}