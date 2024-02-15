#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#include "client.hpp"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ADRESS_IP "127.0.0.1"

static int iResult = 0;
static SOCKET ConnectSocket = INVALID_SOCKET;

static int client()
{
    WSADATA wsaData;

    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    ZeroMemory(&hints, sizeof(hints));

    // Initialize Winsock 
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ADRESS_IP, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ptr = result;
    // Attempt to connect to an address until one succeeds

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to server
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("Error for socket server : %ld\n", WSAGetLastError());
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);
    // printf("avant test connexion...\n");

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server! %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Connection au serveur OK !\n");
    recvData();
    
    while (!end)
    {
        switch (state)
        {
        case NotRecv:
            break;
        case IsSend:
            sendData(importFromMorpion);
            toggle();
            break;
        case IsRecv:
            recvData();
            toggle();
            break;
        default:
            break;
        }
    }

    //return 0;
}

static int killClient()
{
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ConnectSocket);
    WSACleanup();
}

static int sendData(const char data[4096])
{
    iResult = send(ConnectSocket, data, (int)strlen(data), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
}

static char* recvData() {
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Socket invalid !!!\n");
    }
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    printf("Avant reception...\n");
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        printf("Received %d bytes from server: %.*s\n", iResult, iResult, recvbuf);
    }
    else if (iResult == 0) {
        printf("Connection closed by server...\n");
    }
    else {
        printf("recv failed with error: %ld\n", WSAGetLastError());
    }
    return recvbuf;
}