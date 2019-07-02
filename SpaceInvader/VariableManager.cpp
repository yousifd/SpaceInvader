#include "VariableManager.h"

VariableManager::VariableManager() {
}

VariableManager::~VariableManager() {
	FindCloseChangeNotification(h);
}

bool VariableManager::Init(const char* _filename) {
	filename = _filename;
	std::ifstream file(filename);
	std::string line;
	std::string qualifier;
	while (std::getline(file, line)) {
		size_t hash_pos = line.find("#");
		if (hash_pos != std::string::npos) { // Qualifier
			qualifier = line.substr(hash_pos+1);
			//printf("Qualifier %s: \n", qualifier.c_str());
			std::pair<std::string, std::map<std::string, std::string>> 
				pair(qualifier, std::map<std::string, std::string>());
			vars.insert(pair);
		} else { // Values
			size_t equals_pos = line.find(" = ");
			if (equals_pos != std::string::npos) {
				std::string key = line.substr(0, equals_pos);
				std::string value = line.substr(equals_pos+3);
				//printf("Key: %s, Value: %s\n", key.c_str(), value.c_str());
				std::pair<std::string, std::string> pair(key, value);
				try {
					vars.at(qualifier).insert(pair);
				} catch (const std::out_of_range&) {
					printf("Failed to add kv pair: (%s, %s) to %s\n", key.c_str(), value.c_str(), qualifier.c_str());
					return false;
				}
			}
		}
	}

#if _WIN32
	const char* path = "D:\\Personal\\Programming\\SpaceInvader\\SpaceInvader\\vars\\";
	h = FindFirstChangeNotificationA(path, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
	if (h == INVALID_HANDLE_VALUE) {
		printf("Failed to get notified about file changes: %lu\n", GetLastError());
		return false;
	}
#endif

	return true;
}

void VariableManager::CheckForChange() {
#if _WIN32

	for (;;) {
		DWORD ret = WaitForSingleObjectEx(h, INFINITE, FALSE);
		//printf("Waiting returned %lu!\n", ret);

		if (ret == WAIT_OBJECT_0) {
			std::map<std::string, std::map<std::string, std::string>> valuesToUpdate;
			std::ifstream file(filename);
			std::string line;
			std::string qualifier;
			while (std::getline(file, line)) {
				size_t hash_pos = line.find("#");
				if (hash_pos != std::string::npos) { // Qualifier
					qualifier = line.substr(hash_pos+1);
				} else { // Values
					size_t equals_pos = line.find(" = ");
					if (equals_pos != std::string::npos) {
						std::string key = line.substr(0, equals_pos);
						std::string value = line.substr(equals_pos+3);
						if (vars.at(qualifier).at(key).compare(value) != 0) {
							//printf("Updating Old Value (%s) to (%s)\n", vars.at(qualifier).at(key).c_str(), value.c_str());
							vars.at(qualifier).at(key) = value;
							std::pair<std::string, std::map<std::string, std::string>> pair(qualifier, std::map<std::string, std::string>());
							valuesToUpdate.insert(pair);
							valuesToUpdate.at(qualifier).insert(std::pair<std::string, std::string>(key, value));
						}
					}
				}
			}

			fflush(stdout);

			//Print();

			for (auto& kv : valuesToUpdate) {
				callbacks[kv.first](kv.second);
			}
		}

		FindNextChangeNotification(h);
	}

#endif
}

void VariableManager::BindCallback(std::string qualifier, std::function<Callback> callback) {
	std::pair<std::string, std::function<Callback>> pair(qualifier, callback);
	try {
		callbacks.insert(pair);
	} catch (const std::out_of_range&) {
		printf("failed to add calback to qualifier %s\n", qualifier.c_str());
	}
}


void VariableManager::Print() {
	for (auto& qualPair : vars) {
		printf("%s: \n", qualPair.first.c_str());
		for (auto& kv : qualPair.second) {
			printf("Key: %s Value: %s\n", kv.first.c_str(), kv.second.c_str());
		}
	}
}
