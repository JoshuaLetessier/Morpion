#pragma once
class Json
{
public:
	Json();
	~Json();

	void importListensocketJson(SOCKET newSocket);
	void importNameJson(std::string newName);
	void importBoolJson(bool newBool);
	void importDateJson(std::time_t newDate);


private:
	json save_systeme;
	json save_morpion;

};

