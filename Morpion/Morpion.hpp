#pragma once 
class Morpion {
public:
	Morpion();
	void handleEvent(sf::Event& event);
	void draw(sf::RenderWindow& window);
	bool checkGameOver() const;
	void switchPlayer();
	void drawCircleR(sf::RenderWindow& window, float x, float y);
	void drawCircle(sf::RenderWindow& window, float x, float y);
	int main();
};