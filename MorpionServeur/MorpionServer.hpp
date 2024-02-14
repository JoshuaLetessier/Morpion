#pragma once 
#include <vector>
class MorpionServer {

public:

	MorpionServer();

	std::vector<std::vector<int>> board;
	int currentPlayer;

	bool handleEvent(int playerX, int playerY);
	bool checkGameOver() const;
	void switchPlayer();
};
const int gridSize = 3;
const int cellSize = 100;
static int iSendResult = 0;
static int iResult = 0;