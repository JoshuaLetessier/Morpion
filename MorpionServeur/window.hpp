#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#define PORT 27015
#define DATA_BUFSIZE 8192
#define DEFAULT_BUFLEN 512
#define WM_SOCKET (WM_USER + 1)
#define MAX_CLIENTS 2

class MyWindow {
public:
    MyWindow();
    ~MyWindow();

    void StartServer();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void CreateSocketInformation(SOCKET s);
    static LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);
    void FreeSocketInformation(SOCKET s);
    void Initialize();
    HWND MakeWorkerWindow(void);

private:
    SOCKET Listen;
    HWND Window;

};