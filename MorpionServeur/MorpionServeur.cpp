#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
//#include <json\json.h>
//#include "..\simdjson\simdjson.h"
#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include "Serve.cpp"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

json save_morpion;

void initJson() 
{
    
}

void importStringJson(std::string newString)
{

}

void importBoolJson(bool newBool) 
{

}

void importDateJson(std::time_t newDate)
{

}


int __cdecl main(void)
{
    initJson();
    //serve();
}