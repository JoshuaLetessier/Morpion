#pragma once

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class Json
{
public:
	Json();
	~Json();

	// Interaction save_systeme
	void importPlayerAdressJson(char newPlayerAdress);
	void importTurnJson(bool newTurn);
	void importDateJson(std::time_t newDate);

	// Interaction save_morpion
	void importName1Json(char newName);
	void importName2Json(char newName);
	void importMoveJson(std::string newMove);
	void importVictoryJson(bool player1Victory);

	// Interaction getters
	std::string getMorpionValue(bool player1, std::string valueName);
	std::string getSystemeValue(std::string valueName);


private:
	json save_systeme;
	json save_morpion;
	std::vector<json> player1Move = {};
	std::vector<json> player2Move = {};

};

