#pragma once 


class Morpion {
public:

	Morpion();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<int>> board;
	int currentPlayer;
	int myPlayerVal;

	bool handleEvent(sf::Event& event, sf::RenderWindow& window);
	void swapPlayer();
	void setTileVal(int targetX, int targetY, int value);
	void draw(sf::RenderWindow& window);
	void drawCircleR(sf::RenderWindow& window, float x, float y);
	void drawCircle(sf::RenderWindow& window, float x, float y);

private:

};
const int gridSize = 3;
const int cellSize = 100;
static Threading clientServe;