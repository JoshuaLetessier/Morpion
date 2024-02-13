#pragma once

class MyWindow {
public:
    MyWindow();
    ~MyWindow();

    void StartServer();
    void Initialize();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void CreateSocketInformation(SOCKET s);
    //LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);
    static void FreeSocketInformation(SOCKET s);
    static HWND MakeWorkerWindow(void);

private:
    SOCKET Listen;
    HWND Window;

};