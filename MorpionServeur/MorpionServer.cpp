#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

//#include <nlohmann\json.hpp>
//using json = nlohmann::json;

#include "MorpionServer.hpp"
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ADRESS_IP "10.1.144.16"

std::string newName = "Leo";
const int gridSize = 3;
const int cellSize = 100;
static int iSendResult = 0;
static int iResult = 0;
static SOCKET ConnectSocket = INVALID_SOCKET;



MorpionServer::MorpionServer()
{
    board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
}

void MorpionServer::handleEvent(int playerX, int playerY)
{
    // case est valide et non occup�e
    if (playerX >= 0 && playerX < gridSize && playerY >= 0 && playerY < gridSize && board[playerY][playerX] == Player::None) {
        board[playerY][playerX] = currentPlayer;
        switchPlayer();

        std::string dataConvert = std::to_string(playerX) + " " + std::to_string(playerY);
        const char* data = dataConvert.c_str();
        sendData(data);
    }
}

void MorpionServer::draw()
{
    /*for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            printf("")
        }
    }*/
}

bool MorpionServer::checkGameOver() const {
    // V�rifier les lignes et colonnes
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

    // V�rifier les diagonales
    if (board[0][0] != Player::None &&
        board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;  // Victoire sur la diagonale principale
    }

    if (board[0][2] != Player::None &&
        board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true;  // Victoire sur l'autre diagonale
    }

    // V�rifier l'�galit�
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == Player::None) {
                return false;  // Il reste des cases vides, le jeu n'est pas �gal
            }
        }
    }

    return true;  // Toutes les cases sont remplies, la partie est �gale
}

void MorpionServer::switchPlayer() {
    currentPlayer = (currentPlayer == Player::CircleRed) ? Player::CircleBalck : Player::CircleRed;
}

//void createJson()
//{
//    // Using user-defined (raw) string literals
//    using namespace nlohmann::literals;
//    json save_morpion = R"(
//  { "name": "inconnu1", "victoire": false,  "date": 0 },
//  { "name": "inconnu2", "victoire": false,  "date": 0 }
//)"_json;
//}

void MorpionServer::editJson(std::string newName, bool newVictory, std::time_t newDate)
{

}

inline int MorpionServer::sendData(const char data[4096])
{

    iResult = send(ConnectSocket, data, (int)strlen(data), 0);

    return 0;
}



int __cdecl main(void)
{
    MorpionServer game;

    WSADATA wsaData;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
            printf("Message received from client: %.*s\n", iResult, recvbuf);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);

        }
        else if (iResult == 0) {
            printf("Connection closing by client...\n");
            break;  // Sortir de la boucle si le client ferme la connexion
        }
        else {

            printf("recv failed with error: %d\n", WSAGetLastError());//client fermé avant
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}