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

//-------------------------------------------
// A function that represents Thread number 1
//-------------------------------------------
DWORD WINAPI Threading::Thread_ws(LPVOID lpParam)
{
    MSG msg;
    client();

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
}