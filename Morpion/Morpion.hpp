#pragma once 
class Morpion {
public:


	Morpion();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<Player>> board;
	Player currentPlayer;

	void handleEvent(sf::Event& event);
	void draw(sf::RenderWindow& window);
	bool checkGameOver() const;
	void switchPlayer();
	void drawCircleR(sf::RenderWindow& window, float x, float y);
	void drawCircle(sf::RenderWindow& window, float x, float y);
};