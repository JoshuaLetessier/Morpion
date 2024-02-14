#undef UNICODE

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include "MorpionServer.hpp"
#include "Threading.hpp"

#include <windows.h>
#include <winbase.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")

MorpionServer morpion;
Threading windowServe;

int main()
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