#pragma once
#include "client.cpp"

class Threading
{
public:
	Threading();

	static DWORD WINAPI Thread_ws(LPVOID lpParam);
	void LaunchThread();

};