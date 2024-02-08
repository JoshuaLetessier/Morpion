#pragma once
class Serve {

<<<<<<< Updated upstream
};
=======
public:

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	int iSendResult;
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	Serve();
	inline int listening();
	inline int killServ();

};






>>>>>>> Stashed changes
