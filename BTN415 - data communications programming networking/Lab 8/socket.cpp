#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socket.h"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

bool Node::dlls_started = false;
int Node::num_nodes = 0;

packet create_packet(const char* from, const char* to, const char* subject, const char* body) {
    packet my_packet;

    my_packet.fromSize = static_cast<int>(std::strlen(from) + 1);
    my_packet.toSize = static_cast<int>(std::strlen(to) + 1);
    my_packet.subjectSize = static_cast<int>(std::strlen(subject) + 1);
    my_packet.bodySize = static_cast<int>(std::strlen(body) + 1);


    my_packet.from = new char[my_packet.fromSize];
    my_packet.to = new char[my_packet.toSize];
    my_packet.subject = new char[my_packet.subjectSize];
    my_packet.body = new char[my_packet.bodySize];


    std::strcpy(my_packet.from, from);
    std::strcpy(my_packet.to, to);
    std::strcpy(my_packet.subject, subject);
    std::strcpy(my_packet.body, body);


    return my_packet;
}

struct serialized_packet packet_serializer(packet my_packet) {
    //beware of Windows completing groups of four bytes
    char* serialized_packet = new char[
        1                     * sizeof(int)  +
        my_packet.fromSize    * sizeof(int)  +
        1                     * sizeof(int)  +
        my_packet.toSize      * sizeof(char) +
        1                     * sizeof(int)  +
        my_packet.subjectSize * sizeof(char) +
        1                     * sizeof(int)  +
        my_packet.bodySize    * sizeof(char)
    ];
    char* auxptr = serialized_packet;
    memcpy(auxptr, &my_packet.fromSize, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    memcpy(auxptr, my_packet.from, my_packet.fromSize * sizeof(char));
    auxptr += my_packet.fromSize * sizeof(char);
    
    memcpy(auxptr, &my_packet.toSize, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    memcpy(auxptr, my_packet.to, my_packet.toSize * sizeof(char));
    auxptr += my_packet.toSize * sizeof(char);

    memcpy(auxptr, &my_packet.subjectSize, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    memcpy(auxptr, my_packet.subject, my_packet.subjectSize * sizeof(char));
    auxptr += my_packet.subjectSize * sizeof(char);

    memcpy(auxptr, &my_packet.bodySize, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    memcpy(auxptr, my_packet.body, my_packet.bodySize * sizeof(char));

    struct serialized_packet output;
    output.data = serialized_packet;
    output.length =
        4 * sizeof(int) +
        my_packet.fromSize * sizeof(int) +
        my_packet.toSize * sizeof(char) +
        my_packet.subjectSize * sizeof(char) +
        my_packet.bodySize * sizeof(char);
    return output;
}

packet packet_deserializer(char* serialized_packet) {
    packet deserialized_packet;
    char* auxptr = serialized_packet;

    memcpy(&deserialized_packet.fromSize, auxptr, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    deserialized_packet.from = new char[deserialized_packet.fromSize];
    memcpy(deserialized_packet.from, auxptr, sizeof(char) * deserialized_packet.fromSize);
    auxptr += deserialized_packet.fromSize * sizeof(char);


    memcpy(&deserialized_packet.toSize, auxptr, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    deserialized_packet.to = new char[deserialized_packet.toSize];
    memcpy(deserialized_packet.to, auxptr, sizeof(char) * deserialized_packet.toSize);
    auxptr += deserialized_packet.toSize * sizeof(char);


    memcpy(&deserialized_packet.subjectSize, auxptr, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    deserialized_packet.subject = new char[deserialized_packet.subjectSize];
    memcpy(deserialized_packet.subject, auxptr, sizeof(char) * deserialized_packet.subjectSize);
    auxptr += deserialized_packet.subjectSize * sizeof(char);


    memcpy(&deserialized_packet.bodySize, auxptr, 1 * sizeof(int));
    auxptr += 1 * sizeof(int);
    deserialized_packet.body = new char[deserialized_packet.bodySize];
    memcpy(deserialized_packet.body, auxptr, sizeof(char) * deserialized_packet.bodySize);


    /*memcpy(deserialized_packet.name, auxptr, 16 * sizeof(char));
    auxptr += 16 * sizeof(char);
    memcpy(&deserialized_packet.flag, auxptr, sizeof(bool));
    auxptr += 1 * sizeof(bool);
    memcpy(&deserialized_packet.size, auxptr, sizeof(int));
    auxptr += 1 * sizeof(int);
    deserialized_packet.letters = new char[deserialized_packet.size];
    memcpy(deserialized_packet.letters, auxptr, sizeof(char) * deserialized_packet.size);*/
    return deserialized_packet;
}

Node::Node() {
    start_dlls();
    num_nodes++;
    this->active_socket = INVALID_SOCKET;
    this->protocol = "tcp";
    this->ip = "127.0.0.1";
    this->port = 27000;
}

Node::Node(std::string ip, int port) {
    start_dlls();
    num_nodes++;
    this->active_socket = INVALID_SOCKET;
    this->ip = ip;
    this->port = port;
}

Node::~Node() {
    closesocket(this->active_socket);
    std::cout << "Closing socket" << std::endl;
    num_nodes--;
    if (num_nodes == 0) {
        WSACleanup();
    }
}

void Node::start_dlls() const {
    if (!dlls_started) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "Could not start DLLs" << std::endl;
            exit(EXIT_FAILURE);
        }
        else {
            dlls_started = true;
        }
    }
}

bool Node::create_socket() {
    if (this->protocol == "tcp") {
        this->active_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else {
        this->active_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }

    if (this->active_socket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

void Node::display_info() const {
    std::cout << "IP: " << this->ip << std::endl;
    std::cout << "port: " << this->port << std::endl;
    std::cout << "protocol: " << this->protocol << std::endl;
    std::cout << "dlls: " << dlls_started << std::endl;
}

Server_TCP::Server_TCP() : Node() {
    this->role = "server";
    this->client_socket = INVALID_SOCKET;
}

Server_TCP::Server_TCP(std::string ip, int port) : Node(ip, port) {
    this->protocol = "tcp";
    this->role = "server";
    this->client_socket = INVALID_SOCKET;
}

Server_TCP::~Server_TCP() {
    closesocket(this->client_socket);
    std::cout << "Closing client socket" << std::endl;
}

bool Server_TCP::bind_socket() {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    SvrAddr.sin_port = htons(this->port);
    if (bind(this->active_socket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr)) == SOCKET_ERROR) {
        std::cout << "Could not bind socket to address" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool Server_TCP::listen_for_connections() {
    if (listen(this->active_socket, 1) == SOCKET_ERROR) {
        std::cout << "Could not start to listen" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool Server_TCP::accept_connection() {
    this->client_socket = accept(this->active_socket, NULL, NULL);
    if (this->client_socket == INVALID_SOCKET) {
        std::cout << "Failed to accept connection" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

int Server_TCP::send_message(std::string message) {
    return send(this->client_socket, message.c_str(), static_cast<int>(message.length()), 0);
}

int Server_TCP::send_packet(packet message) {
    struct serialized_packet serialized = packet_serializer(message);
    return send(this->client_socket, serialized.data, serialized.length, 0);
}

int Server_TCP::receive_message(std::string& message) {
    char RxBuffer[MAX_BUFFER_SIZE] = {};
    memset(RxBuffer, 0, MAX_BUFFER_SIZE);
    int num_bytes = recv(this->client_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
    message = RxBuffer;
    return num_bytes;
}

int Server_TCP::receive_packet(packet& my_packet) {
    char RxBuffer[MAX_BUFFER_SIZE] = {};
    memset(RxBuffer, 0, MAX_BUFFER_SIZE);
    int num_bytes = recv(this->client_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
    my_packet = packet_deserializer(RxBuffer);
    return num_bytes;
}

void Server_TCP::close_connection() {
    closesocket(this->client_socket);
}

Client_TCP::Client_TCP() : Node() {
    this->protocol = "tcp";
    this->role = "client";
}

bool Client_TCP::connect_socket(std::string ip, int port) {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(port);
    SvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    if ((connect(this->active_socket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
        std::cout << "Failed to connect to server" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

int Client_TCP::send_message(std::string message) {
    return send(this->active_socket, message.c_str(), static_cast<int>(message.length()), 0);
}

int Client_TCP::send_packet(packet message) {
    struct serialized_packet serialized = packet_serializer(message);
    return send(this->active_socket, serialized.data, serialized.length, 0);
}

int Client_TCP::receive_message(std::string& message) {
    char RxBuffer[MAX_BUFFER_SIZE] = {};
    memset(RxBuffer, 0, MAX_BUFFER_SIZE);
    int num_bytes = recv(this->active_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
    message = RxBuffer;
    return num_bytes;
}

int Client_TCP::receive_packet(packet& my_packet) {
    char RxBuffer[MAX_BUFFER_SIZE] = {};
    memset(RxBuffer, 0, MAX_BUFFER_SIZE);
    int num_bytes = recv(this->active_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
    my_packet = packet_deserializer(RxBuffer);
    return num_bytes;
}

Client_UDP::Client_UDP() : Node() {
    this->protocol = "udp";
    this->role = "client";
}

int Client_UDP::send_message(std::string message, std::string ip, int port) {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(port);
    SvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    return sendto(this->active_socket, message.c_str(), static_cast<int>(message.length()), 0,
        (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));
}

struct sockaddr_in Client_UDP::receive_message(std::string& message) {
    struct sockaddr_in SvrAddr;
    int addr_len = sizeof(SvrAddr);

    char RxBuffer[128] = {};
    recvfrom(this->active_socket, RxBuffer, sizeof(RxBuffer), 0,
        (struct sockaddr*)&SvrAddr, &addr_len);
    message = RxBuffer;
    return SvrAddr;
}

Server_UDP::Server_UDP() : Node() {
    this->protocol = "udp";
    this->role = "server";
}

Server_UDP::Server_UDP(std::string ip, int port) : Node(ip, port) {
    this->protocol = "udp";
    this->role = "server";
}

bool Server_UDP::bind_socket() {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    SvrAddr.sin_port = htons(this->port);
    if (bind(this->active_socket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr)) == SOCKET_ERROR) {
        std::cout << "Could not bind socket to address" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

int Server_UDP::send_message(std::string message, std::string ip, int port) {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(port);
    SvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    return sendto(this->active_socket, message.c_str(), static_cast<int>(message.length()), 0,
        (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));
}

struct sockaddr_in Server_UDP::receive_message(std::string& message) {
    struct sockaddr_in SvrAddr;
    int addr_len = sizeof(SvrAddr);

    char RxBuffer[128] = {};
    recvfrom(this->active_socket, RxBuffer, sizeof(RxBuffer), 0,
        (struct sockaddr*)&SvrAddr, &addr_len);
    message = RxBuffer;
    return SvrAddr;
}