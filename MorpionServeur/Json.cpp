//// Librairies necessaires
//#include <fstream>
//#include "Serve.cpp"/*
//#include <nlohmann\json.hpp>
//using json = nlohmann::json;*/
//
//// Le header après les forwards declare
//#include "Json.hpp"
//
//Json::Json()
//{
//	save_systeme["socket_info"]["default_port"] = DEFAULT_PORT;
//}
//
//Json::~Json()
//{
//	std::fstream file("save.json");
//	file << save_systeme << save_morpion;
//}
//
///////////////////////////////////////////////////////////////
///*                 Interaction save_systeme                */
///////////////////////////////////////////////////////////////
//
//void Json::importListenSocketJson(addrinfo* newSocket) // Enregistre le socket d'écoute du serveur
//{
//	if (!save_systeme["socket_info"]["listen_socket"])
//	{
//		
//		//save_systeme["socket_info"]["listen_socket"] = newSocket;
//	}
//}
//
//void Json::importPlayerSocketJson(SOCKET newPlayerSocket) // Enregistre les sockets des joueurs lorsqu'elles sont différentes
//{
//	if (!save_systeme["socket_info"]["player1_socket"])
//	{
//		save_systeme["socket_info"]["player1_socket"] = newPlayerSocket;
//	}
//	else if (save_systeme["socket_info"]["player1_socket"] != newPlayerSocket)
//	{
//		save_systeme["socket_info"]["player2_socket"] = newPlayerSocket;
//	}
//	std::cout << save_systeme << std::endl;
//}
//
//void Json::importTurnJson(bool newTurn) // Enregistre le tour du joueur en cours
//{
//	if (!save_systeme["player_info"]["turn"])
//	{
//		save_systeme["player_info"]["turn"] = newTurn;
//	}
//	else
//	{
//		save_systeme["player_info"].erase("turn");
//		save_systeme["player_info"]["turn"] = newTurn;
//	}
//}
//
//void Json::importDateJson(std::time_t newDate) // Enregistre la date de la partie
//{
//	if (!save_systeme["socket_info"]["date"])
//	{
//		save_systeme["socket_info"]["date"] = newDate;
//	}
//}
//
///////////////////////////////////////////////////////////////
///*                 Interaction save_morpion                */
///////////////////////////////////////////////////////////////
//
//void Json::importName1Json(std::string newName) // Enregistre le nom du joueur 1
//{
//	if (!save_morpion["player1"]["name"])
//	{
//		save_morpion["player1"]["name"] = newName;
//	}
//}
//
//void Json::importName2Json(std::string newName) // Enregistre le nom du joueur 2
//{
//	if (!save_morpion["player2"]["name"])
//	{
//		save_morpion["player2"]["name"] = newName;
//	}
//}
//
//void Json::importMoveJson(std::string newMove) // Enregistre le dernier mouvement
//{
//	if (!save_morpion["player1"]["victory"] && !save_morpion["player2"]["victory"])
//	{
//		if (save_morpion["player1"]["turn"] == true )
//		{
//			if (!save_morpion["player1"]["move"])
//			{
//				save_morpion["player1"]["move"] = newMove;
//			}
//			else
//			{
//				save_morpion["player1"].erase("move");
//				save_morpion["player1"]["move"] = newMove;
//			}
//		}
//		else
//		{
//			if (!save_morpion["player2"]["move"])
//			{
//				save_morpion["player2"]["move"] = newMove;
//			}
//			else
//			{
//				save_morpion["player2"].erase("move");
//				save_morpion["player2"]["move"] = newMove;
//			}
//		}
//	}
//}
//
//void Json::importVictoryJson(bool player1Victory) // Enregistre la victoire
//{
//	if (!save_morpion["player1"]["victory"])
//	{
//		save_morpion["player1"]["victory"] = player1Victory;
//	}
//	if (!save_morpion["player2"]["victory"])
//	{
//		save_morpion["player2"]["victory"] = !player1Victory;
//	}
//}