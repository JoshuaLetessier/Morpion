#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        //std::cerr << "Erreur lors de l'initialisation de Winsock." << std::endl;
        return 1;
    }

    // Création du socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création de la socket." << std::endl;
        WSACleanup();
        return 1;
    }
    else
    {
        std::cerr << "socket créer" << std::endl;
    }


    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);

    if (inet_addr("142.250.178.142") == INADDR_NONE) {
        std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    serverAddress.sin_addr.s_addr = inet_addr("142.250.178.142");


    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cerr << "serveur créer" << std::endl;
    }

    //requete
    const char* request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    int stockRequest = send(clientSocket, request, strlen(request), 0);// envoie de la requete

    if (stockRequest == -1)
    {
        printf("Erreur lors de l'envoi de la requête");
    }
    else {

        printf("La requête a été envoyée avec succès\n");
        char buffer[4096];
        int revceve = recv(clientSocket, buffer, sizeof(buffer), 0);//reponse

        std::cout.write(buffer, revceve);
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
