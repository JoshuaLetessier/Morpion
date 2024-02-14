#pragma once 
#include <vector>
#include "Json.hpp"
class MorpionServer {

public:

	MorpionServer();
	~MorpionServer();

	std::vector<std::vector<int>> board;
	int currentPlayer;
	bool handleEvent(int playerX, int playerY);
	bool checkGameOver() const;
	void switchPlayer();
	bool turn;
	Json save;
};