#pragma once
#include <crow/app.h>
#include <cstring>
#include "ConfigController.h"

namespace validator 
{
	bool isMissingParameter(char* parameter);
	bool isContainsParameter(std::string parameter_name);
	int isInvalidParameter(char* parameter);
	bool checkRange(int parameter, int min, int max);
	bool checkBodyEmpty(crow::request req);
	bool checkCorrectParseJson(std::string str);
	bool checkCorrectParameters(json object, std::vector<std::string> parameters);
	json setSettingsParameter(std::string parameter_name, char* parameter);
	json addMode(crow::request req);
}