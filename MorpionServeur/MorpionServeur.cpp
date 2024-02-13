﻿#undef UNICODE

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

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ADRESS_IP "10.1.144.16"

#include "MorpionServer.hpp"

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

void MorpionServer::switchPlayer() 
{
    turn != turn;
    save.importTurnJson(turn);
    currentPlayer = (currentPlayer == Player::CircleRed) ? Player::CircleBalck : Player::CircleRed;
}

inline int MorpionServer::sendData(const char data[4096])
{
    iResult = send(ConnectSocket, data, (int)strlen(data), 0);
    return 0;
}

int __cdecl MorpionServer::main(void)
{
    iSendResult = 0;
    iResult = 0;
    ConnectSocket = INVALID_SOCKET;
    turn = false;
    //MorpionServer game;
    OutputDebugStringA("on lance le serv \n");
    //game.serve();

    return 0;
}