#pragma once


class Threading
{
public:
	Threading();

	UINT MyThreadProc(LPVOID pParam);
	void LaunchThread();

private:
	
};