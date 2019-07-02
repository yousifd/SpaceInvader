#pragma once;

#include <fstream>
#include <stdexcept>
#include <string>
#include <map>
#include <functional>

#if _WIN32
#include <windows.h>
#include <fileapi.h>
#endif

#include "Player.h"

typedef void(Callback)(const std::map<std::string, std::string>&);

class VariableManager {
public:
	VariableManager();
	~VariableManager();

	bool Init(const char* filename);
	void CheckForChange();
	void BindCallback(std::string qualifier, std::function<Callback> callback);
	void Print();

	std::map<std::string, std::map<std::string, std::string>> vars;
	std::map<std::string, std::function<Callback>> callbacks;

	HANDLE h;

private:
	const char* filename;
};