#pragma once 
#include <vector>
class MorpionServer {

public:

	MorpionServer();

	std::vector<std::vector<int>> board;
	int currentPlayer;
	bool handleEvent(int playerX, int playerY);
	void draw();
	bool checkGameOver() const;
	void switchPlayer();
};