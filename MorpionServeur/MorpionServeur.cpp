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
#define ADRESS_IP "10.1.144.16"

json save_morpion;
const char* newName = "Leo";

void initJson() 
{
    // Using user-defined (raw) string literals
    using namespace nlohmann::literals;
    save_morpion = R"(
  { "name1": "inconnu", "victoire": false,  "date": 0 },
  { "name2": "inconnu", "victoire": false,  "date": 0 }
)"_json;
}

void editJson(const char* newName, bool newVictory, std::time_t newDate)
{
    //save_morpion["name1"_json_pointer] = newName;
    std::cout << save_morpion.dump(3) << std::endl;
}




int __cdecl main(void)
{
    initJson();
    //editJson(newName, false, 0);
    //serve();
}