#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ClientThreading.hpp"

Threading::Threading()
{}

//-------------------------------------------
// A function that represents Thread number 1
//-------------------------------------------
DWORD WINAPI Threading::Thread_Send_cs(LPVOID lpParam)
{
   
    while (true)
    {
        int sendData(const char data[4096]);
    }
    return 0;
}

DWORD WINAPI Threading::Thread_Recv_cs(LPVOID lpParam)
{
    while (true)
    {
        recvData();
    }
    return 0;
}

void Threading::LaunchThread(int value)
{
   
    // Data of Thread 1
    int Data_Of_Thread_send = 1;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_send = 0;
    

    // Data of Thread 1
    int Data_Of_Thread_recv = 2;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_recv = 0;

    // Aray to store thread handles 
    HANDLE Array_Of_Thread_Handles[2];

    
    // Create thread 1.
    if (value == 0)
    {
       
        Handle_Of_Thread_send = CreateThread(NULL, 0, Thread_Send_cs, &Data_Of_Thread_send, 0, NULL);
        if (Handle_Of_Thread_send == NULL)
            ExitProcess(Data_Of_Thread_send);
    }
    else if (value == 1)
    {
        printf("second thread\n");
        Handle_Of_Thread_recv = CreateThread(NULL, 0, Thread_Recv_cs, &Data_Of_Thread_recv, 0, NULL);
        if (Handle_Of_Thread_recv == NULL)
            ExitProcess(Data_Of_Thread_recv);
    }
    

   



    Array_Of_Thread_Handles[0] = Handle_Of_Thread_send;
    Array_Of_Thread_Handles[1] = Handle_Of_Thread_recv;

    // Wait until all threads have terminated.
   // WaitForSingleObject(Array_Of_Thread_Handles[0], INFINITE);
    WaitForMultipleObjects(3, Array_Of_Thread_Handles, TRUE, INFINITE);


    // Close all thread handles upon completion.
    CloseHandle(Handle_Of_Thread_send);
    CloseHandle(Handle_Of_Thread_recv);
}