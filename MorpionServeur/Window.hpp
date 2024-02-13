#pragma once

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
        const char* color;
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

private:
    SOCKET Listen;
    HWND Window;

};
// Global var
extern MyWindow::LPSOCKET_INFORMATION SocketInfoList;

static char recvbuf[DEFAULT_BUFLEN];
static bool firstSocket;