#pragma once 
#include <vector>
class MorpionServer {

public:

	MorpionServer();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<Player>> board;
	Player currentPlayer ;
	inline int __cdecl serve();
	void handleEvent(int playerX, int playerY);
	void draw();
	bool checkGameOver() const;
	void switchPlayer();
	inline int sendData(const char data[4096]);
	int __cdecl main(void);
};