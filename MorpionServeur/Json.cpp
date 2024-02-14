// Librairies necessaires
#include <fstream>
#include <format>
#include "Serve.cpp"/*
#include <nlohmann\json.hpp>
using json = nlohmann::json;*/

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

/////////////////////////////////////////////////////////////
/*                 Interaction save_systeme                */
/////////////////////////////////////////////////////////////

void Json::importPlayerAdressJson(char newPlayerAdress) // Enregistre les sockets des joueurs lorsqu'elles sont différentes
{
	if (!save_systeme["player1_adress"])
	{
		save_systeme["player1_adress"] = newPlayerAdress;
	}
	else if (save_systeme["player1_adress"] != newPlayerAdress)
	{
		save_systeme["player2_adress"] = newPlayerAdress;
	}
}

void Json::importTurnJson(bool newTurn) // Enregistre le tour du joueur en cours
{
	if (!save_systeme["player_turn"])
	{
		save_systeme["player_turn"] = newTurn;
	}
	else
	{
		save_systeme.erase("player_turn");
		save_systeme["player_turn"] = newTurn;
	}
}

void Json::importDateJson(std::time_t newDate) // Enregistre la date de la partie
{
	if (!save_systeme["date"])
	{
		save_systeme["date"] = newDate;
	}
}

/////////////////////////////////////////////////////////////
/*                 Interaction save_morpion                */
/////////////////////////////////////////////////////////////

void Json::importName1Json(char newName) // Enregistre le nom du joueur 1
{
	if (!save_morpion["player1"]["name"])
	{
		save_morpion["player1"]["name"] = newName;
	}
}

void Json::importName2Json(char newName) // Enregistre le nom du joueur 2
{
	if (!save_morpion["player2"]["name"])
	{
		save_morpion["player2"]["name"] = newName;
	}
}

void Json::importMoveJson(std::string newMove) // Enregistre le dernier mouvement
{
	if (!save_morpion["player1"]["victory"] && !save_morpion["player2"]["victory"])
	{
		printf("coucou\n");
		if (save_morpion["player1"]["turn"] == true )
		{
			printf("coucou\n");
			if (!save_morpion["player1"]["move"])
			{
				save_morpion["player1"]["move"] = newMove;
			}
			else
			{
				save_morpion["player1"].erase("move");
				save_morpion["player1"]["move"] = newMove;
				std::cout << save_morpion << std::endl;
			}
		}
		else
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

void Json::importVictoryJson(bool player1Victory) // Enregistre la victoire
{
	if (!save_morpion["player1"]["victory"])
	{
		save_morpion["player1"]["victory"] = player1Victory;
	}
	if (!save_morpion["player2"]["victory"])
	{
		save_morpion["player2"]["victory"] = !player1Victory;
	}
}

////////////////////////////////////////////////////////
/*                 Interaction getters                */
////////////////////////////////////////////////////////

std::string Json::getMorpionValue(bool player1, std::string valueName)
{
	return save_morpion[player1 ? "player1" : "player2"][valueName];
}

std::string Json::getSystemeValue(std::string valueName)
{
	return save_systeme[valueName];
}