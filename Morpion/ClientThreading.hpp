#pragma once

#include <tchar.h>
#include <strsafe.h>
#include "client.cpp"

class Threading
{
public:
	Threading();

	static DWORD WINAPI Thread_cs(LPVOID lpParam);
	void LaunchThread();

};