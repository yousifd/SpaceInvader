#include "VariableManager.h"

VariableManager::VariableManager() {
}

VariableManager::~VariableManager() {
}

bool VariableManager::Init(const char* filename) {
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

	// TODO: Update if file is updated (written to)

	return true;
}

//void VariableManager::CheckForChange() {
//
//}

//void VariableManager::BindPlayerCallback(PlayerCallback call) {
//	playercallback = call;
//	//std::pair<std::string, callback> pair("Player", call);
//	//try {
//	//	callbacks.insert(pair);
//	//} catch (const std::out_of_range&) {
//	//	printf("Failed to add callback to qualifier %s\n", qualifier.c_str());
//	//}
//}

void VariableManager::Print() {
	for (auto& qualPair : vars) {
		printf("%s: \n", qualPair.first.c_str());
		for (auto& kv : qualPair.second) {
			printf("Key: %s Value: %s\n", kv.first.c_str(), kv.second.c_str());
		}
	}
}
