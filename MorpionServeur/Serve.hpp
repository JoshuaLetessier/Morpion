#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma prefast(suppress : 28251, "Cette instance contient aucune annotation.")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#pragma comment(lib, "ws2_32.lib")

class Serve {

public:

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	int iSendResult;
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	Serve();
	inline int listen();
	inline int killServ();

};