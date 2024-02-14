#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")
// #pragma comment (lib, "Mswsock.lib")

#include "MorpionServer.hpp"
#include "Threading.hpp"
#include "Window.hpp"

// typedef definition


MyWindow::MyWindow() : Listen(INVALID_SOCKET), Window(NULL)
{}

MyWindow::~MyWindow() {
	WSACleanup();
}

void MyWindow::StartServer() {
	Initialize();

	// Boucle de messages de fenêtre
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void MyWindow::Initialize() {
	WSADATA wsaData;
	if (WSAStartup((2, 2), &wsaData) != 0) {
		printf("WSAStartup() a échoué avec l'erreur %d\n", WSAGetLastError());
		return;
	}

	// Initialiser la fenêtre
	Window = MakeWorkerWindow();
	if (Window == NULL) {
		printf("MakeWorkerWindow() a échoué !\n");
		return;
	}
}

LRESULT CALLBACK MyWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SOCKET Accept;
	LPSOCKET_INFORMATION SocketInfo;
	DWORD RecvBytes;
	DWORD SendBytes;
	DWORD Flags;

	if (uMsg == WM_SOCKET)
	{
		if (WSAGETSELECTERROR(lParam))
		{
			printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
			FreeSocketInformation(wParam);
		}
		else
		{
			printf("Socket looks fine!\n");

			switch (WSAGETSELECTEVENT(lParam))
			{
			case FD_ACCEPT:
				if ((Accept = accept(wParam, NULL, NULL)) == INVALID_SOCKET)
				{
					printf("accept() failed with error %d\n", WSAGetLastError());
					break;
				}
				else
				{
					printf("accept() is OK!\n");
				}

				// Create a socket information structure to associate with the socket for processing I/O
				CreateSocketInformation(Accept);
				printf("Socket number  connected\n");
				WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);

				break;

			case FD_READ:
				SocketInfo = GetSocketInformation(wParam);

				// Read data only if the receive buffer is empty
				/*if (SocketInfo == NULL)
				{
					printf("SocketInfo Null");
					return;
				}*/
				if (SocketInfo->BytesRECV != 0)
				{
					SocketInfo->RecvPosted = TRUE;
					return 0;
				}
				else
				{
					SocketInfo->DataBuf.buf = SocketInfo->Buffer;
					SocketInfo->DataBuf.len = DATA_BUFSIZE;
					Flags = 0;
					if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("WSARecv() failed with error %d\n", WSAGetLastError());
							FreeSocketInformation(wParam);
							return 0;
						}
					}
					else // No error so update the byte count
					{
						printf("WSARecv() is OK!\n");
						SocketInfo->DataBuf.buf[RecvBytes] = 0;
						OutputDebugStringA(SocketInfo->DataBuf.buf);
						SocketInfo->BytesRECV = RecvBytes;
						int result = recv(SocketInfo->Socket, recvbuf, (int)strlen(recvbuf), 0);
						if (result > 0)
						{
							printf("%.*s\n", result, recvbuf);
						}
						if (strcmp(SocketInfo[0].color, "black") == 0) {
							std::string data;
							data.resize(20);
							sprintf_s(&data[0], data.size(), " %d", result);
							if (sizeof(data) == 5)
							{
								save.importMoveJson(data);
							}
							// Envoie les données à l'autre socket
							//send(SocketInfo[1].Socket, data.c_str(), (int)strlen(data.c_str()), 0);//pb ici à régler 
						}
						else
						{
							char data[20];
							sprintf_s(data, sizeof(data), " %d", result);
							// Envoie les données à l'autre socket
							//send(SocketInfo[2].Socket, data, (int)strlen(data), 0);
						}
					}
				}
				break;
				// DO NOT BREAK HERE SINCE WE GOT A SUCCESSFUL RECV. Go ahead
				// and begin writing data to the client

			case FD_CLOSE:
				printf("Closing socket \n");
				FreeSocketInformation(wParam);
				break;
			}
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void MyWindow::CreateSocketInformation(SOCKET s)
{
	LPSOCKET_INFORMATION SI;
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
		}
		else
		{
			printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");
			if (firstSocket)
			{
				const char* colorPlayer = "black";
				send(s, colorPlayer, (int)strlen(colorPlayer), 0);
				SI->Socket = s;
				SI->RecvPosted = FALSE;
				SI->BytesSEND = 0;
				SI->BytesRECV = 0;
				SI->Next = SocketInfoList;
				SocketInfoList = SI;
				SI->color = colorPlayer;
				firstSocket = false;
				break;
			}
			else
			{
				const char* colorPlayer = "red";
				send(s, colorPlayer, (int)strlen(colorPlayer), 0);
				SI->Socket = s;
				SI->RecvPosted = FALSE;
				SI->BytesSEND = 0;
				SI->BytesRECV = 0;
				SI->Next = SocketInfoList;
				SocketInfoList = SI;
				SI->color = colorPlayer;
				break;
			}
		}
	}
	// Prepare SocketInfo structure for use
}

MyWindow::LPSOCKET_INFORMATION MyWindow::GetSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION* SI = SocketInfoList;
	while (SI)
	{
		if (SI->Socket == s)
			return SI;

		SI = SI->Next;
	}
	return NULL;
}

void MyWindow::FreeSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION* SI = SocketInfoList;
	SOCKET_INFORMATION* PrevSI = NULL;
	while (SI)
	{
		if (SI->Socket == s)
		{
			if (PrevSI)
				PrevSI->Next = SI->Next;

			else
				SocketInfoList = SI->Next;

			closesocket(SI->Socket);
			GlobalFree(SI);
			return;
		}
		PrevSI = SI;
		SI = SI->Next;
	}
}

HWND MyWindow::MakeWorkerWindow(void)
{
	WNDCLASS wndclass;
	const CHAR* ProviderClass = "AsyncSelect";
	HWND Window;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = (LPCWSTR)ProviderClass;

	if (RegisterClass(&wndclass) == 0)
	{
		printf("RegisterClass() failed with error %d\n", GetLastError());
		return NULL;
	}
	else
		printf("RegisterClass() is OK!\n");

	// Create a window
	if ((Window = CreateWindow((LPCWSTR)ProviderClass, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL)) == NULL)
	{
		printf("CreateWindow() failed with error %d\n", GetLastError());
		return NULL;
	}
	else
		printf("CreateWindow() is OK!\n");
	//ShowWindow(Window, SW_SHOW);
	return Window;

}

int MyWindow::LaunchServ() {
	DWORD Ret;
	SOCKET Listen;
	SOCKADDR_IN InternetAddr;
	HWND Window;
	WSADATA wsaData;
	MorpionServer Mserve;
	std::cout << "LaunchServ" << std::endl;

	if ((Window = MyWindow::MakeWorkerWindow()) == NULL)
	{
		printf("MakeWorkerWindow() failed!\n");
		return 1;
	}
	else
		printf("MakeWorkerWindow() is OK!\n");

	// Prepare echo server
	if (WSAStartup((2, 2), &wsaData) != 0)
	{
		printf("WSAStartup() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("WSAStartup() is OK!\n");

	if ((Listen = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("socket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("socket() is pretty fine!\n");

	if (WSAAsyncSelect(Listen, Window, WM_SOCKET, FD_ACCEPT | FD_CLOSE) == 0)
		printf("WSAAsyncSelect() is OK lol!\n");
	else
		printf("WSAAsyncSelect() failed with error code %d\n", WSAGetLastError());

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(PORT);

	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("bind() is OK maaa!\n");

	if (listen(Listen, 5))
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("listen() is also OK! I am listening now...\n");

	// Translate and dispatch window messages for the application thread

	while (Ret = GetMessage(&msg, NULL, 0, 0))
	{
		if (Ret == -1)
		{
			//printf("\nGetMessage() failed with error %d\n", GetLastError());
			return 1;
		}
		else
		{
			//printf("\nGetMessage() is pretty fine!\n");
		}
		//printf("Translating a message...\n");
		TranslateMessage(&msg);
		//printf("Dispatching a message...\n");
		DispatchMessage(&msg);
	}
}