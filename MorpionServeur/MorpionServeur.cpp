#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
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
std::string newName = "Leo";

void createJson() 
{
    // Using user-defined (raw) string literals
    using namespace nlohmann::literals;
    json save_morpion = R"(
  { "name": "inconnu1", "victoire": false,  "date": 0 },
  { "name": "inconnu2", "victoire": false,  "date": 0 }
)"_json;
}

void editJson(std::string newName, bool newVictory, std::time_t newDate)
{

}


int __cdecl main(void)
{
    serve();
}