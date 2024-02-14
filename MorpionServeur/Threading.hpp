#pragma once

#include "Window.hpp"

class Threading : public MyWindow
{
public:
	Threading();

	static void DisplayMessage(HANDLE hScreen, char* ThreadName, int Data, int Count);
	static DWORD WINAPI Thread_ws(LPVOID lpParam);
	void LaunchThread();

private:
	static MyWindow windowInstance;
	
};