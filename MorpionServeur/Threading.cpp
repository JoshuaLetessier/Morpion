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
    StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
    WriteConsole(hScreen, msgBuf, cchStringSize, &dwChars, NULL);
    Sleep(1000);
}

//-------------------------------------------
// A function that represents Thread number 1
//-------------------------------------------
DWORD WINAPI Threading::Thread_no_1(LPVOID lpParam)
{
    // creation de window + sockets
    // boucle getmessage main
    // boucle getmessage thread

    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;

    // Get Handle To screen.
    // Else how will we print?
    if ((hStdout =
        GetStdHandle(STD_OUTPUT_HANDLE))
        == INVALID_HANDLE_VALUE)
        return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam);

    for (count = 0; count <= 4; count++)
    {
        DisplayMessage(hStdout, "Thread_no_1", Data, count);
    }

    return 0;
}

//-------------------------------------------
// A function that represents Thread number 2
//-------------------------------------------
DWORD WINAPI Threading::Thread_no_2(LPVOID lpParam)
{
    // serveur web
    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;

    // Get Handle To screen. Else how will we print?
    if ((hStdout =
        GetStdHandle(STD_OUTPUT_HANDLE)) ==
        INVALID_HANDLE_VALUE)
        return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam);

    for (count = 0; count <= 7; count++)
    {
        DisplayMessage(hStdout, "Thread_no_2", Data, count);
    }

    return 0;
}

void Threading::LaunchThread()
{
    // Data of Thread 1
    int Data_Of_Thread_1 = 1;
    // Data of Thread 2
    int Data_Of_Thread_2 = 2;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_1 = 0;
    // variable to hold handle of Thread 1 
    HANDLE Handle_Of_Thread_2 = 0;
    // Aray to store thread handles 
    HANDLE Array_Of_Thread_Handles[2];

    // Create thread 1.
    Handle_Of_Thread_1 = CreateThread(NULL, 0, Thread_no_1, &Data_Of_Thread_1, 0, NULL);
    if (Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);

    // Create thread 2.
    Handle_Of_Thread_2 = CreateThread(NULL, 0, Thread_no_2, &Data_Of_Thread_2, 0, NULL);
    if (Handle_Of_Thread_2 == NULL)
        ExitProcess(Data_Of_Thread_2);


    // Store Thread handles in Array of Thread
    // Handles as per the requirement
    // of WaitForMultipleObjects() 
    Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
    Array_Of_Thread_Handles[1] = Handle_Of_Thread_2;

    // Wait until all threads have terminated.
    WaitForMultipleObjects(2,
        Array_Of_Thread_Handles, TRUE, INFINITE);

    printf("Since All threads executed"
        " lets close their handles \n");

    // Close all thread handles upon completion.
    CloseHandle(Handle_Of_Thread_1);
    CloseHandle(Handle_Of_Thread_2);
}