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

void Json::importListenSocketJson(SOCKET newSocket)
{
	if (!save_systeme["socket_info"]["listen_socket"])
	{
		save_systeme["socket_info"]["listen_socket"] = newSocket;
	}
}

void Json::importPlayerSocketJson(SOCKET newPlayerSocket)
{
	if (!save_systeme["socket_info"]["player1_socket"])
	{
		save_systeme["socket_info"]["player1_socket"] = newPlayerSocket;
	}
	else if (save_systeme["socket_info"]["player1_socket"] != newPlayerSocket)
	{
		save_systeme["socket_info"]["player2_socket"] = newPlayerSocket;
	}
}

void Json::importDateJson(std::time_t newDate)
{
	if (!save_systeme["socket_info"]["date"])
	{
		save_systeme["socket_info"]["date"] = newDate;
	}
}

void Json::importName1Json(std::string newName)
{
	if (!save_morpion["player1"]["name"])
	{
		save_morpion["player1"]["name"] = newName;
	}
}

void Json::importName2Json(std::string newName)
{
	if (!save_morpion["player2"]["name"])
	{
		save_morpion["player2"]["name"] = newName;
	}
}

void Json::importTurnJson(bool newTurn)
{
	if (!save_systeme["player_info"]["turn"])
	{
		save_systeme["player_info"]["turn"] = newTurn;
	}
	else
	{
		save_systeme["player_info"].erase("turn");
		save_systeme["player_info"]["turn"] = newTurn;
	}
}

void Json::importMoveJson(std::string player, std::string newMove)
{
	if (!save_morpion["player1"]["victory"] && !save_morpion["player2"]["victory"])
	{
		if (save_morpion["player1"]["name"] == player )
		{
			if (!save_morpion["player1"]["move"])
			{
				save_morpion["player1"]["move"] = newMove;
			}
			else
			{
				save_morpion["player1"].erase("move");
				save_morpion["player1"]["move"] = newMove;
			}
		}
		if (save_morpion["player2"]["name"] == player)
		{
			if (!save_morpion["player2"]["move"])
			{
				save_morpion["player2"]["move"] = newMove;
			}
			else
			{
				save_morpion["player2"].erase("move");
				save_morpion["player2"]["move"] = newMove;
			}
		}
	}
}

void Json::importVictoryJson(bool player1Victory, bool player2Victory)
{
	if (!save_morpion["player1"]["victory"])
	{
		save_morpion["player1"]["victory"] = player1Victory;
	}
	if (!save_morpion["player2"]["victory"])
	{
		save_morpion["player2"]["victory"] = player2Victory;
	}
}