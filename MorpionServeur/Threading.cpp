#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <stdio.h>

#define BUF_SIZE 255

#include "Threading.hpp"

Threading::Threading()
{}

//------------------------------------------
// A function to Display the message
// indicating in which tread we are
//------------------------------------------
void Threading::DisplayMessage(HANDLE hScreen, char* ThreadName, int Data, int Count)
{
    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    // Print message using thread-safe functions.
    StringCchPrintf(msgBuf, BUF_SIZE,
        TEXT("Executing iteration %02d of %s"
            " having data = %02d \n"),
        Count, ThreadName, Data);
    StringCchLengthW(msgBuf, BUF_SIZE, &cchStringSize);
    WriteConsole(hScreen, msgBuf, cchStringSize, &dwChars, NULL);
    Sleep(1000);
}

//-------------------------------------------
// A function that represents Thread number 1
//-------------------------------------------
DWORD WINAPI Threading::Thread_ws(LPVOID lpParam)
{
    windowInstance.LaunchServ();
    return 0;
}

void Threading::LaunchThread()
{
    // Data of Thread 1
    int Data_Of_Thread_ws = 1;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_ws = 0;
    // Aray to store thread handles 
    HANDLE Array_Of_Thread_Handles[1];

    // Create thread 1.
    Handle_Of_Thread_ws = CreateThread(NULL, 0, Thread_ws, &Data_Of_Thread_ws, 0, NULL);
    if (Handle_Of_Thread_ws == NULL)
        ExitProcess(Data_Of_Thread_ws);

    Array_Of_Thread_Handles[0] = Handle_Of_Thread_ws;

    // Wait until all threads have terminated.
    WaitForSingleObject(Array_Of_Thread_Handles[0], INFINITE);

    // Close all thread handles upon completion.
    CloseHandle(Handle_Of_Thread_ws);
    //CloseHandle(Handle_Of_Thread_2);
}