#include <SFML/Graphics.hpp>
#include <iostream>

#include "Morpion.hpp"
#include "client.cpp"

#define WM_SOCKET (WM_USER + 1)

const int gridSize = 3;
const int cellSize = 100;

inline int client();
inline int killClient();

Morpion game;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LPSOCKET_INFORMATION SocketInfoList;

Morpion::Morpion() 
{
    // Initialiser la grille avec des valeurs par défaut
    board = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
    currentPlayer = 1;
    myPlayerVal = 1;

}

bool Morpion::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (myPlayerVal != currentPlayer)
    {
        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        int mouseX = event.mouseButton.x / cellSize;
        int mouseY = event.mouseButton.y / cellSize;

        if (mouseX >= 0 && mouseX < gridSize && mouseY >= 0 && mouseY < gridSize &&
            board[mouseY][mouseX] == 0) {
            board[mouseY][mouseX] = currentPlayer;
        }

        std::string dataConvert = std::to_string(mouseX) + " " + std::to_string(mouseY);
        const char* data = dataConvert.c_str();

        sendData(data);

        return true;
    }
    return false;
}

void Morpion::swapPlayer()
{
    if (currentPlayer == 1)
        currentPlayer = 2;
    else
        currentPlayer = 1;
}

void Morpion::setTileVal(int targetX, int targetY, int value)
{
    board[targetY][targetX] = value;
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

            // Le joueur ROUGE place un pion
            if (board[i][j] == 1)
            {
                drawCircleR(window, j * cellSize, i * cellSize);
            }
            // Le joueur NOIR place un pion
            else if (board[i][j] == 2)
            {
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

HWND MakeWorkerWindow(void)
{
    WNDCLASS wndclass;
    const CHAR* ProviderClass = "AsyncSelect";
    HWND Window;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = (WNDPROC)WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = (LPCWSTR)ProviderClass;

    if (RegisterClass(&wndclass) == 0)
    {
        printf("RegisterClass() failed with error %d\n", GetLastError());
        return NULL;
    }
    else
        printf("RegisterClass() is OK!\n");

    // Create a window

    if ((Window = CreateWindow((LPCWSTR)ProviderClass, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL)) == NULL)
    {
        printf("CreateWindow() failed with error %d\n", GetLastError());
        return NULL;
    }
    else
        printf("CreateWindow() is OK!\n");

    return Window;

}

int WINAPI main() {

    HWND Window;

    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Morpion Joueur contre Joueur");

    client();
    MakeWorkerWindow();

    //if (WSAStartup((2, 2), &wsaData) != 0)
    //{
    //    printf("WSAStartup() failed with error %d\n", WSAGetLastError());
    //    return 1;
    //}
    //else
    //    printf("WSAStartup() is OK!\n");

    //if ((Listen = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    //{
    //    printf("socket() failed with error %d\n", WSAGetLastError());
    //    return 1;
    //}
    //else
    //    printf("socket() is pretty fine!\n");

    //if (WSAAsyncSelect(Listen, Window, WM_SOCKET, FD_ACCEPT | FD_READ | FD_CLOSE) == 0)
    //    printf("WSAAsyncSelect() is OK lol!\n");
    //else
    //    printf("WSAAsyncSelect() failed with error code %d\n", WSAGetLastError());

    while (window.isOpen()) {
       
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                killClient();
            }
            //si la methode read est ok
            //alors recvData()
            if (game.handleEvent(event, window))
            {
                
            }
        }
        game.draw(window);
        
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LPSOCKET_INFORMATION SocketInfo;
    SocketInfo = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION));
    SocketInfo->Socket = ConnectSocket;
    SOCKET Accept;
    DWORD RecvBytes;
    DWORD SendBytes;
    DWORD Flags;

    printf("callback \n");

    if (uMsg == WM_SOCKET)
    {
        if (WSAGETSELECTERROR(lParam))
        {
            printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
        }
        else
        {
            printf("Socket looks fine!\n");
            switch (WSAGETSELECTEVENT(lParam))
            {

            case FD_READ:

                SocketInfo->Socket = ConnectSocket;

                if (SocketInfo->BytesRECV != 0)
                {
                    SocketInfo->RecvPosted = TRUE;
                    return 0;
                }
                else
                {
                    SocketInfo->DataBuf.buf = SocketInfo->Buffer;
                    SocketInfo->DataBuf.len = DEFAULT_BUFLEN;

                    if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, 0, NULL, NULL) == SOCKET_ERROR)
                    {
                        if (WSAGetLastError() != WSAEWOULDBLOCK)
                        {
                            printf("WSARecv() failed with error %d\n", WSAGetLastError());
                            return 0;
                        }

                    }
                    else // No error so update the byte count
                    {

                        char* data = recvData();

                        int newPosX = (int)data[0] - 48;
                        int newPosY = (int)data[2] - 48;
                        int curPlayer = (int)data[4] - 48;
                        printf("data printed from morpion.cpp: %d, %d, %d", newPosX, newPosY, curPlayer);

                        game.currentPlayer = curPlayer;

                        game.setTileVal(newPosX, newPosY, game.currentPlayer);
                        if (RecvBytes == 0)
                        {
                            printf("Socket deconnecté \n");
                        }
                        SocketInfo->BytesRECV = 0;
                    }
                }
                break;
            }
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}