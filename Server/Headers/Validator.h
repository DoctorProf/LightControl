#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <crow/app.h>

using json = nlohmann::json;

namespace validator 
{
	bool missingParameter(char* parameter);
	int invalidParameter(char* parameter);
	bool checkRange(int parameter, int min, int max);
	bool checkBodyEmpty(crow::request req);
	bool checkCorrectParseJson(crow::request req);
	bool checkCorrectParameters(json mode, std::vector<std::string> parameters);
	json setParameter(char* parameter, std::string name_parameter, int min, int max);
	json addMode(crow::request req);
}