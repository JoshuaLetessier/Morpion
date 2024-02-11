#pragma once 
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
	void editJson(std::string newName, bool newVictory, std::time_t newDate);
	inline int sendData(const char data[4096]);
};