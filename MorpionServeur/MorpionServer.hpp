#pragma once 
#include <vector>
#include "Json.hpp"
class MorpionServer {

public:

	MorpionServer();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<Player>> board;
	Player currentPlayer;
	void handleEvent(int playerX, int playerY);
	void draw();
	bool checkGameOver() const;
	void switchPlayer();
	inline int sendData(const char data[4096]);
	int __cdecl main(void);

private:
	const int gridSize = 3;
	const int cellSize = 100;
	int iSendResult;
	int iResult;
	SOCKET ConnectSocket;
	bool turn;
	Json save;
};