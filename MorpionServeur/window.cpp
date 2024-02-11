#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "MorpionServer.hpp"


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")
// #pragma comment (lib, "Mswsock.lib")
#define PORT 27015
#define DATA_BUFSIZE 8192

#define WM_SOCKET (WM_USER + 1)

// typedef definition

typedef struct _SOCKET_INFORMATION {

    BOOL RecvPosted;

    CHAR Buffer[DATA_BUFSIZE];

    WSABUF DataBuf;

    SOCKET Socket;

    DWORD BytesSEND;

    DWORD BytesRECV;

    struct _SOCKET_INFORMATION* Next;

} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

// Prototypes

void CreateSocketInformation(SOCKET s);

LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);

void FreeSocketInformation(SOCKET s);

HWND MakeWorkerWindow(void);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Global var

LPSOCKET_INFORMATION SocketInfoList;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    MSG msg;

    DWORD Ret;

    SOCKET Listen;

    SOCKADDR_IN InternetAddr;

    HWND Window;

    WSADATA wsaData;

    
    MorpionServer();

    if ((Window = MakeWorkerWindow()) == NULL)

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

            printf("\nGetMessage() failed with error %d\n", GetLastError());

            return 1;

        }

        else

            printf("\nGetMessage() is pretty fine!\n");



        printf("Translating a message...\n");

        TranslateMessage(&msg);

        printf("Dispatching a message...\n");

        DispatchMessage(&msg);

    }
    MorpionServer game;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

                WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

                break;

            case FD_READ:

                SocketInfo = GetSocketInformation(wParam);

                // Read data only if the receive buffer is empty

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
                    if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes,&Flags, NULL, NULL) == SOCKET_ERROR)
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

                    }

                }

                // DO NOT BREAK HERE SINCE WE GOT A SUCCESSFUL RECV. Go ahead

                // and begin writing data to the client

            case FD_WRITE:

                SocketInfo = GetSocketInformation(wParam);

                if (SocketInfo->BytesRECV > SocketInfo->BytesSEND)

                {

                    SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;

                    SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;



                    if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0,

                        NULL, NULL) == SOCKET_ERROR)

                    {

                        if (WSAGetLastError() != WSAEWOULDBLOCK)

                        {

                            printf("WSASend() failed with error %d\n", WSAGetLastError());

                            FreeSocketInformation(wParam);

                            return 0;

                        }

                    }

                    else // No error so update the byte count

                    {

                        printf("WSASend() is OK!\n");

                        SocketInfo->BytesSEND += SendBytes;

                    }

                }



                if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)

                {

                    SocketInfo->BytesSEND = 0;

                    SocketInfo->BytesRECV = 0;

                    // If a RECV occurred during our SENDs then we need to post an FD_READ notification on the socket

                    if (SocketInfo->RecvPosted == TRUE)

                    {

                        SocketInfo->RecvPosted = FALSE;

                        PostMessage(hwnd, WM_SOCKET, wParam, FD_READ);

                    }

                }

                break;

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



void CreateSocketInformation(SOCKET s)

{

    LPSOCKET_INFORMATION SI;



    if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)

    {

        printf("GlobalAlloc() failed with error %d\n", GetLastError());

        return;

    }

    else

        printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");



    // Prepare SocketInfo structure for use

    SI->Socket = s;

    SI->RecvPosted = FALSE;

    SI->BytesSEND = 0;

    SI->BytesRECV = 0;

    SI->Next = SocketInfoList;

    SocketInfoList = SI;

}



LPSOCKET_INFORMATION GetSocketInformation(SOCKET s)
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



void FreeSocketInformation(SOCKET s)

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



HWND MakeWorkerWindow(void)

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

    if ((Window = CreateWindow(

        (LPCWSTR)ProviderClass,

        L"",

        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT,

        CW_USEDEFAULT,

        CW_USEDEFAULT,

        CW_USEDEFAULT,

        NULL,

        NULL,

        NULL,

        NULL)) == NULL)

    {

        printf("CreateWindow() failed with error %d\n", GetLastError());

        return NULL;

    }

    else

        printf("CreateWindow() is OK!\n");

    ShowWindow(Window, SW_SHOW);
    return Window;

}

