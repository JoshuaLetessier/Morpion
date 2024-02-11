#pragma once

class Server {
public:
    Server();
    ~Server();

    void Run();
    inline int serve(void);

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

    HINSTANCE hInstance;
    HWND hwnd;

};