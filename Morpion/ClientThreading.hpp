#pragma once
#include "client.cpp"

class Threading
{
public:
	Threading();

	static DWORD __stdcall Thread_Send_cs(LPVOID lpParam);

	static DWORD __stdcall Thread_Recv_cs(LPVOID lpParam);

	
	void LaunchThread(int value);

};