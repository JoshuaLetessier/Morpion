#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>

#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include "Serve.cpp"
#include "MorpionServer.hpp"
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ADRESS_IP "10.1.144.16"

std::string newName = "Leo";

void MorpionServer::MorpionInit()
{
    gridSize = 3;
    cellSize = 100;
    board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
}

void MorpionServer::handleEvent(int playerX, int playerY)
{
    // case est valide et non occupée
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

void MorpionServer::switchPlayer() {
    currentPlayer = (currentPlayer == Player::CircleRed) ? Player::CircleBalck : Player::CircleRed;
}

void createJson() 
{
    // Using user-defined (raw) string literals
    using namespace nlohmann::literals;
    json save_morpion = R"(
  { "name": "inconnu1", "victoire": false,  "date": 0 },
  { "name": "inconnu2", "victoire": false,  "date": 0 }
)"_json;
}

void editJson(std::string newName, bool newVictory, std::time_t newDate)
{

}


int __cdecl main(void)
{
    MorpionServer game;

    serve();
}