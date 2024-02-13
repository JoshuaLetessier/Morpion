#pragma once


class Threading
{
public:
	Threading();

	static void DisplayMessage(HANDLE hScreen, char* ThreadName, int Data, int Count);
	static DWORD WINAPI Thread_no_1(LPVOID lpParam);
	static DWORD WINAPI Thread_no_2(LPVOID lpParam);
	void LaunchThread();

private:
	
};