#pragma once
#include <windows.h>
#include <winsock2.h>
#include "Json.hpp"
#include "MorpionServer.hpp"

#define DEFAULT_BUFLEN 512
#define DATA_BUFSIZE 8192
#define PORT 27015
#define WM_SOCKET (WM_USER + 1)
#define MAX_CLIENTS 2

class MyWindow {
public:

    MyWindow();
    ~MyWindow();

    typedef struct _SOCKET_INFORMATION
    {
        BOOL RecvPosted;
        CHAR Buffer[DATA_BUFSIZE];
        WSABUF DataBuf;
        SOCKET Socket;
        DWORD BytesSEND;
        DWORD BytesRECV;
        struct _SOCKET_INFORMATION* Next;
        int color;
    } SOCKET_INFORMATION, * LPSOCKET_INFORMATION;


    static SOCKET_INFORMATION clientSockets[MAX_CLIENTS];

    
    //LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);

    void StartServer();
    void Initialize();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void CreateSocketInformation(SOCKET s);
    static LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);
    static void FreeSocketInformation(SOCKET s);
    static HWND MakeWorkerWindow(void);
    static void UpdateClient(LPSOCKET_INFORMATION SocketInfo, DWORD RecvBytes);
    static int LaunchServ();

private:
    SOCKET Listen;
    HWND Window;

};
// Global var
static Json save;
static MorpionServer Mserve;
static MSG msg;
static MyWindow::LPSOCKET_INFORMATION SocketInfoList;
static char recvbuf[DEFAULT_BUFLEN];
static bool firstSocket;
static int SocketNumber = 0;