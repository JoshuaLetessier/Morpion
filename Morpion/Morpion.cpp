#include <SFML/Graphics.hpp>
#include <iostream>

#include "Morpion.hpp"
#include "client.cpp"

const int gridSize = 3;
const int cellSize = 100;

inline int client(char* callback);
inline int killClient();



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Exécuter le client lorsque la fenêtre est créée
        //if (client(callback) != 0) {
        //    MessageBox(hwnd, L"Erreur lors de l'exécution du client", L"Erreur", MB_OK | MB_ICONERROR);
        //    PostQuitMessage(1);
        //}
        break;
    case WM_DESTROY:
        // Terminer le client et quitter l'application lors de la fermeture de la fenêtre
        killClient();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

Morpion::Morpion() : currentPlayer(Player::CircleRed) {
    // Initialiser la grille avec des valeurs par défaut
    board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
}

void Morpion::handleEvent(sf::Event& event, sf::RenderWindow& window) {
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
                //drawCircleR(window, j * cellSize, i * cellSize);
            }
            else if (board[i][j] == Player::CircleBalck) {
               // drawCircle(window, j * cellSize, i * cellSize);
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

int WINAPI main(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    char cServerCallback[512];
    client(cServerCallback);
   
    // Définir les paramètres de la fenêtre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MainWindowClass";

    // Enregistrer la classe de fenêtre
    RegisterClass(&wc);

    // Créer la fenêtre
    HWND hWnd = CreateWindowEx(0, L"MainWindowClass", L"Fenêtre Windows avec connexion au serveur", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL) {
        return 1;
    }

    // Afficher la fenêtre
    ShowWindow(hWnd, nCmdShow);
    
    // Boucle de messages
    MSG msg = {};
   /* while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }*/

    OutputDebugStringA("toujour co \n");
    //std::string player1Name;
    //std::string player2Name;
    //std::cout << "Entrez le nom du Joueur 1 (X) : ";
    //std::cin >> player1Name;
    //sendData(player1Name.c_str());
    //std::cout << "Entrez le nom du Joueur 2 (O) : ";
    //std::cin >> player2Name;
    //sendData(player2Name.c_str());
 /*   std::string player1Name = getPlayerName();
    if (player1Name.empty()) {
        MessageBox(NULL, L"Nom de joueur non valide. Fermeture de l'application.", L"Erreur", MB_OK | MB_ICONERROR);
        return 1;
    }

    sendData(player1Name.c_str());*/

    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Morpion Joueur contre Joueur");

    Morpion game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                killClient();
            }

            game.handleEvent(event, window);
        }

        game.draw(window);
        if (cServerCallback == "") {
            std::cout << "La partie est terminée !" << std::endl;
            window.close();
        }
    }
    return 0;
}