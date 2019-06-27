#pragma once;

#include "Player.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <map>

//typedef void(*callback)(std::map<std::string, std::string>);
typedef void(Player::*PlayerCallback)(std::map<std::string, std::string>);

class VariableManager {
public:
	VariableManager();
	~VariableManager();

	bool Init(const char* filename);
	//void BindPlayerCallback(PlayerCallback call);
	//void AddCallback(std::string qualifier, callback call);
	void Print();

	std::map<std::string, std::map<std::string, std::string>> vars;
	PlayerCallback playercallback;
};