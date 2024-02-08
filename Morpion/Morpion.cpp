#include <SFML/Graphics.hpp>
#include <iostream>

#include "Morpion.hpp"
#include "client.cpp"

const int gridSize = 3;
const int cellSize = 100;


Morpion::Morpion() : currentPlayer(Player::CircleRed) {
    // Initialiser la grille avec des valeurs par défaut
    board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
}


void Morpion::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        int mouseX = event.mouseButton.x / cellSize;
        int mouseY = event.mouseButton.y / cellSize;

        std::string dataConvert = std::to_string(mouseX) + " " + std::to_string(mouseY);
        const char* data = dataConvert.c_str();
        sendData(data);
    }
}


void Morpion::draw(sf::RenderWindow& window) {
    window.clear();

    // Dessiner la grille
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            // Dessiner X ou O
            if (board[i][j] == Player::CircleRed) {
                drawCircleR(window, j * cellSize, i * cellSize); 
            }
            else if (board[i][j] == Player::CircleBalck) {
                drawCircle(window, j * cellSize, i * cellSize);
            }
        }
    }

    window.display();
}

void Morpion::drawCircleR(sf::RenderWindow& window, float x, float y) {
    sf::CircleShape circle(cellSize / 2 - 10);
    circle.setPosition(x + 10, y + 10);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Red);
    circle.setFillColor(sf::Color::Transparent);
    window.draw(circle);
}

void Morpion::drawCircle(sf::RenderWindow& window, float x, float y) {
    sf::CircleShape circle(cellSize / 2 - 10);
    circle.setPosition(x + 10, y + 10);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    circle.setFillColor(sf::Color::Transparent);
    window.draw(circle);
}

int main() {

    char cServerCallback[512];

    client(cServerCallback);

    std::string playerName;

    std::cout << "Entrez votre nom de joueur: ";
    std::cin >> playerName;

    sendData(playerName.c_str());

    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Morpion Joueur contre Joueur");

    Morpion game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                killClient();
            }

            game.handleEvent(event);
        }

        game.draw(window);
        if (cServerCallback == "") {
            std::cout << "La partie est terminée !" << std::endl;
            window.close();
        }
    }

    return 0;
}