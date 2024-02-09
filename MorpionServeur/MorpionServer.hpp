#pragma once 
#include <vector>
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
};