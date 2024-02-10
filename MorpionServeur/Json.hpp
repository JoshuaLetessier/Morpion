#pragma once

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class Json
{
public:
	Json();
	~Json();

	// Interaction save_systeme
	void importListenSocketJson(addrinfo* newSocket);
	void importPlayerSocketJson(SOCKET newPlayerSocket);
	void importTurnJson(bool newTurn);
	void importDateJson(std::time_t newDate);

	// Interaction save_morpion
	void importName1Json(std::string newName);
	void importName2Json(std::string newName);
	void importMoveJson(std::string newMove);
	void importVictoryJson(bool player1Victory);


private:
	json save_systeme;
	json save_morpion;
	std::vector<json> player1Move = {};
	std::vector<json> player2Move = {};

};

