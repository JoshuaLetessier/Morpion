#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <afxmt.h>

#include "Threading.h"

class CWinThread : public CCmdTarget;

//CWinThread* AfxBeginThread(
//    AFX_THREADPROC pfnThreadProc,
//    LPVOID pParam,
//    int nPriority = THREAD_PRIORITY_NORMAL,
//    UINT nStackSize = 0,
//    DWORD dwCreateFlags = 0,
//    LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

Threading::Threading() // Constructeur
{

}

UINT Threading::MyThreadProc(LPVOID pParam)
{
    Threading* pObject = (Threading*)pParam;

    if (pObject == NULL || !pObject->IsKindOf(RUNTIME_CLASS(Threading)))
        return 1;   // if pObject is not valid

    // do something with 'pObject'

    return 0;   // thread completed successfully
}


void Threading::LaunchThread() // Fonction de lancement du thread
{
    pNewObject = new Threading;
    AfxBeginThread(MyThreadProc, pNewObject);
	UINT MyControllingFunction(LPVOID pParam);
}