#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ADRESS_IP "127.0.0.1"

static int iResult = 0;
static SOCKET ConnectSocket = INVALID_SOCKET;

inline int sendData(const char data[4096]);


inline int client()
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

    printf("avant test connexion...\n");

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server! %ld\n", WSAGetLastError());

        WSACleanup();
        return 1;
    }
    
    const char* data = "connexionnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";

    iResult = send(ConnectSocket, data, (int)strlen(data), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    else
        printf("messagge send\n");

    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        printf("Message received from server: %.*s\n", iResult, recvbuf);


    }
    else if (iResult == 0) {
        printf("Connection closed by server...\n");
    }
    else {
        printf("recv failed with error: %d\n", WSAGetLastError());
    }
    return 0;
}

inline int killClient()
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

inline int sendData(const char data[4096])
{
    iResult = send(ConnectSocket, data, (int)strlen(data), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

   
}


//inline int recvData()
//{
//    char recvbuf[DEFAULT_BUFLEN];
//    int recvbuflen = DEFAULT_BUFLEN;
//    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//    if (iResult > 0) {
//        printf("Message received from server: %.*s\n", iResult, recvbuf);
//
//    }
//    return 0;
//}