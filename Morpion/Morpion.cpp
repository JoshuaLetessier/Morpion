#include <SFML/Graphics.hpp>
#include <iostream>

const int gridSize = 3;
const int cellSize = 100;

enum class Player { None, Cross, Circle };

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::Cross) {
        // Initialiser la grille
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                board[i][j] = Player::None;
            }
        }

       
        std::cout << "Entrez le nom du Joueur 1 (X) : ";
        std::cin >> player1Name;
        std::cout << "Entrez le nom du Joueur 2 (O) : ";
        std::cin >> player2Name;
    }

    void handleEvent(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            int mouseX = event.mouseButton.x / cellSize;
            int mouseY = event.mouseButton.y / cellSize;

            // case est valide et non occupée
            if (mouseX >= 0 && mouseX < gridSize && mouseY >= 0 && mouseY < gridSize &&
                board[mouseY][mouseX] == Player::None) {
                board[mouseY][mouseX] = currentPlayer;
                switchPlayer();
            }
        }
    }

    void draw(sf::RenderWindow& window) {
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
                if (board[i][j] == Player::Cross) {
                    drawCircleR(window, j * cellSize, i * cellSize);
                }
                else if (board[i][j] == Player::Circle) {
                    drawCircle(window, j * cellSize, i * cellSize);
                }
            }


        }

        window.display();
    }

    bool checkGameOver() const {
        // Vérifier les lignes et colonnes
        for (int i = 0; i < gridSize; ++i) {
            if (board[i][0] != Player::None &&
                board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true;  // Victoire sur la ligne i
            }

            if (board[0][i] != Player::None &&
                board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return true;  // Victoire sur la colonne i
            }
        }

        // Vérifier les diagonales
        if (board[0][0] != Player::None &&
            board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return true;  // Victoire sur la diagonale principale
        }

        if (board[0][2] != Player::None &&
            board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return true;  // Victoire sur l'autre diagonale
        }

        // Vérifier l'égalité
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (board[i][j] == Player::None) {
                    return false;  // Il reste des cases vides, le jeu n'est pas égal
                }
            }
        }

        return true;  // Toutes les cases sont remplies, la partie est égale
    }


private:
    Player currentPlayer;
    Player board[gridSize][gridSize];
    std::string player1Name;
    std::string player2Name;

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::Cross) ? Player::Circle : Player::Cross;
    }

    void drawCircleR(sf::RenderWindow& window, float x, float y) {
        sf::CircleShape circle(cellSize / 2 - 10);
        circle.setPosition(x + 10, y + 10);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Red);
        circle.setFillColor(sf::Color::Transparent);
        window.draw(circle);
    }

    void drawCircle(sf::RenderWindow& window, float x, float y) {
        sf::CircleShape circle(cellSize / 2 - 10);
        circle.setPosition(x + 10, y + 10);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setFillColor(sf::Color::Transparent);
        window.draw(circle);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Morpion Joueur contre Joueur");

    TicTacToe game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            game.handleEvent(event);
        }

        game.draw(window);
        if (game.checkGameOver()) {
            std::cout << "La partie est terminée !" << std::endl;
        }
    }

    return 0;
}
