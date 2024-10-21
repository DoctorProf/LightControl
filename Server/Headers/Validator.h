#pragma once
#include <crow/app.h>
#include <cstring>
#include "ConfigController.h"

namespace validator 
{
	bool missingParameter(char* parameter);
	int invalidParameter(char* parameter);
	bool checkRange(int parameter, int min, int max);
	bool checkBodyEmpty(crow::request req);
	bool checkCorrectParseJson(std::string str);
	bool checkCorrectParameters(json object, std::vector<std::string> parameters);
	json setParameter(char* parameter, std::string name_parameter, int min, int max);
	json addMode(crow::request req);
}