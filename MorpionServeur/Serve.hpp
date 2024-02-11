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