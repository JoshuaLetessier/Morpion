#pragma once 
class Morpion {
public:

	Morpion();

	enum class Player { None, CircleRed, CircleBalck };
	std::vector<std::vector<Player>> board;
	Player currentPlayer;

	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void drawCircleR(sf::RenderWindow& window, float x, float y);
	void drawCircle(sf::RenderWindow& window, float x, float y);
};