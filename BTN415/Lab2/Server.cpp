// Name : Mansoor Zafar 
// Date : 2024-02-02
// ID   : 100503226
// BTN415 NCC Lab 2

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_CHAR_SEND 128
#define LBS_TO_KG 2.205
#include <iostream>
#include <winsock2.h>
#include <string>
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

    std::cout << "Waiting for client connection" << std::endl;

    SOCKET ClientSocket;

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Failed to accept connection" << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

    closesocket(ListenSocket);
    std::cout << "Connection Established" << std::endl;

    char RxBuffer[128] = {};
    recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
    std::cout << "Msg Rx: " << RxBuffer << std::endl;
    float weight = static_cast<float>(std::atof(RxBuffer) / LBS_TO_KG);

    std::string TxBuffer{"The weight in kg is : " + std::to_string(weight)};
    
    send(ClientSocket, TxBuffer.c_str(), MAX_CHAR_SEND, 0);
    //Client only accepts 128 char, so we can only send 128 characters

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}
