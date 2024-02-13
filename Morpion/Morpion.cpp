#include <SFML/Graphics.hpp>
#include <iostream>

#include "Morpion.hpp"
#include "client.cpp"

const int gridSize = 3;
const int cellSize = 100;

inline int client(char* callback);
inline int killClient();

Morpion::Morpion() : currentPlayer(Player::CircleRed) {
    // Initialiser la grille avec des valeurs par défaut
    board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
}

bool Morpion::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        int mouseX = event.mouseButton.x / cellSize;
        int mouseY = event.mouseButton.y / cellSize;

        if (mouseX >= 0 && mouseX < gridSize && mouseY >= 0 && mouseY < gridSize &&
            board[mouseY][mouseX] == Player::None) {
            board[mouseY][mouseX] = currentPlayer;
        }

        std::string dataConvert = std::to_string(mouseX) + " " + std::to_string(mouseY);
        const char* data = dataConvert.c_str();
        OutputDebugStringA("event detecte \n");
        sendData(data);

        return true;
    }
    return false;
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

    OutputDebugStringA("dessins \n");
    sf::CircleShape circle(cellSize / 2 - 10);
    circle.setPosition(x + 10, y + 10);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    circle.setFillColor(sf::Color::Transparent);
    window.draw(circle);
}

std::string getPlayerName() {
    sf::RenderWindow nameWindow(sf::VideoMode(400, 200), "Morpion");
    sf::Font font;
    //if (!font.loadFromFile("Billie-Eilish.ttf")) {
    //    return "erreur font";  // Ou une autre valeur d'erreur si nécessaire
    //}


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 50);
    text.setString("Entrez votre nom : ");

    sf::String inputText;
    sf::Text inputDisplay;
    inputDisplay.setFont(font);
    inputDisplay.setCharacterSize(24);
    inputDisplay.setFillColor(sf::Color::White);
    inputDisplay.setPosition(50, 100);

    while (nameWindow.isOpen()) {
        sf::Event event;
        while (nameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                nameWindow.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !inputText.isEmpty()) { // Backspace
                    inputText.erase(inputText.getSize() - 1, 1);
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    inputText += event.text.unicode;
                }
                inputDisplay.setString(inputText);
            }
        }

        nameWindow.clear();
        nameWindow.draw(text);
        nameWindow.draw(inputDisplay);
        nameWindow.display();
    }

    return inputText.toAnsiString();
}

int main() {

    client();
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Morpion Joueur contre Joueur");

    Morpion game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                killClient();
            }

            if (game.handleEvent(event, window))
                recvData();
        }

        game.draw(window);

    }
    return 0;
}