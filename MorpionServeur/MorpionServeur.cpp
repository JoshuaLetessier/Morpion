#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Serve.hpp"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Ex�cuter le client lorsque la fen�tre est cr��e
        if (Serve() != 0) {
            MessageBox(hwnd, L"Erreur lors de l'ex�cution du client", L"Erreur", MB_OK | MB_ICONERROR);
            PostQuitMessage(1);
        }
        break;
    case WM_DESTROY:
        // Terminer le client et quitter l'application lors de la fermeture de la fen�tre
        Serve::killServ();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // D�fin les param�tres de la fen�tre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MainWindowClass";

    // Enregistrer la classe de fen�tre
    RegisterClass(&wc);

    // Cr�er la fen�tre
    HWND hWnd = CreateWindowEx(0, L"MainWindowClass", L"Fen�tre Windows avec connexion au serveur", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL) {
        return 1;
    }

    // Afficher la fen�tre
    ShowWindow(hWnd, nCmdShow);

    // Boucle de messages
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    listen();
    killServ();



int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    Server server;
    server.Run();
    return 0;
}