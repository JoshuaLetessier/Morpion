#pragma once 
class MorpionServer {

private:
	int gridSize;
	int cellSize;

public:

	void MorpionInit();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<Player>> board;
	Player currentPlayer;

	void handleEvent(int playerX, int playerY);
	void draw();
	bool checkGameOver() const;
	void switchPlayer();
};