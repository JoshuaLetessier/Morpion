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
//static SOCKET ConnectSocket = INVALID_SOCKET;


MorpionServer::MorpionServer()
{
       board = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));   
}

bool MorpionServer::handleEvent(int playerX, int playerY)
{
    printf("handle cote serveur\n");
   

    printf("%d \n", board[playerX][playerY]);
    if (playerX >= 0 && playerX < gridSize && playerY >= 0 && playerY < gridSize && board[playerX][playerY] == 0)
    {
        board[playerX][playerY] = 1;
        printf("%d \n", board[playerX][playerY]);
        //switchPlayer();
        return true;
    } 
    else
    {
        return false;
    }
    return false;
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
    //// V�rifier les lignes et colonnes
    //for (int i = 0; i < gridSize; ++i) {
    //    if (board[i][0] != Player::None &&
    //        board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
    //        return true;  // Victoire sur la ligne i
    //    }

    //    if (board[0][i] != Player::None &&
    //        board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
    //        return true;  // Victoire sur la colonne i
    //    }
    //}

    //// V�rifier les diagonales
    //if (board[0][0] != Player::None &&
    //    board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    //    return true;  // Victoire sur la diagonale principale
    //}

    //if (board[0][2] != Player::None &&
    //    board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    //    return true;  // Victoire sur l'autre diagonale
    //}

    //// V�rifier l'�galit�
    //for (int i = 0; i < gridSize; ++i) {
    //    for (int j = 0; j < gridSize; ++j) {
    //        if (board[i][j] == Player::None) {
    //            return false;  // Il reste des cases vides, le jeu n'est pas �gal
    //        }
    //    }
    //}

    return true;  // Toutes les cases sont remplies, la partie est �gale
}

void MorpionServer::switchPlayer() {
    //currentPlayer = (currentPlayer == Player::CircleRed) ? Player::CircleBalck : Player::CircleRed;
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

void editJson(std::string newName, bool newVictory, std::time_t newDate)
{

}

