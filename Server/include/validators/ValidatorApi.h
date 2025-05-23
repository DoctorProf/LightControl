#pragma once
#include <crow/app.h>
#include <cstring>
#include <format>
#include <regex>
#include <string>
#include "../controllers/ConfigController.h"

namespace validator_api
{
	bool isMissingParameter(char* value);
	bool isContainsParameter(std::string param_name, json object);
	int isInvalidParameterInt(char* value);
	float isInvalidParameterFloat(char* value);
	bool checkRange(int value, int min, int max);
	bool checkRange(float value, float min, float max);
	bool checkCorrectHex(std::string hex);

	json checkCorrectBrightness(std::string parame_name, char* value);
	json checkCorrectState(std::string param_name, char* value);
	json checkCorrectModeName(std::string param_name, char* value);

	json setSettingsParameter(std::string param_name, char* value);
	json setModeParameter(std::string param_name, std::string internal_param, char* value);
}