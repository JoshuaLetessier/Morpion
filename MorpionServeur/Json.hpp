#pragma once
class Json
{
public:
	Json();
	~Json();

	void importListenSocketJson(SOCKET newSocket);
	void importPlayerSocketJson(SOCKET newPlayerSocket);
	void importDateJson(std::time_t newDate);
	void importName1Json(std::string newName);
	void importName2Json(std::string newName);
	void importTurnJson(bool newTurn);
	void importMoveJson(std::string player, std::string newMove);
	void importVictoryJson(bool player1Victory, bool player2Victory);


private:
	json save_systeme;
	json save_morpion;
	std::vector<json> player1Move = {};
	std::vector<json> player2Move = {};

};

