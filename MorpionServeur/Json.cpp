// Librairies necessaires
#include <fstream>
#include <nlohmann\json.hpp>
using json = nlohmann::json;
#include "Serve.cpp"

// Le header après les forwards declare
#include "Json.hpp"

Json::Json()
{
	save_systeme["socket_info"]["default_port"] = DEFAULT_PORT;
}

Json::~Json()
{
	std::fstream file("save.json");
	file << save_systeme << save_morpion;
}

void Json::importListensocketJson(SOCKET newSocket)
{
	save_systeme["socket_info"]["listen_socket"] = newSocket;
}

void Json::importListensocketJson(SOCKET newSocket)
{
	save_systeme["socket_info"]["listen_socket"] = newSocket;
}

void Json::importNameJson(std::string newName)
{
	if (save_morpion["player1"]["client_socket"] = "#client_socket")
	{
		save_morpion["player1"]["name"] = newName;
	}
	else
	{
		save_morpion["player2"]["name"] = newName;
	}
}

void Json::importBoolJson(bool newBool)
{

}

void Json::importDateJson(std::time_t newDate)
{

}

