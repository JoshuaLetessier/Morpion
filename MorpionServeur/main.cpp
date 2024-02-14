

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include "MorpionServer.hpp"
#include "Threading.hpp"




MorpionServer morpion;
Threading windowServe;

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int playerMove = NULL;
	windowServe.LaunchThread();
	//boucle morpion
	while (!morpion.checkGameOver())
	{
		if (playerMove)
		{
			//char[5] Json;
			morpion.switchPlayer();
		}
	}
	return 0;
}