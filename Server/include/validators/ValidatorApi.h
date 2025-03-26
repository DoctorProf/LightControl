#pragma once
#include <crow/app.h>
#include <cstring>
#include <format>
#include "../controllers/ConfigController.h"

namespace validator_api
{
	bool isMissingParameter(char* parameter);
	bool isContainsParameter(std::string parameter_name, json object);
	int isInvalidParameterInt(char* parameter);
	float isInvalidParameterFloat(char* parameter);
	bool checkRange(int parameter, int min, int max);
	bool checkRange(float parameter, float min, float max);

	json checkCorrectBrightness(std::string parameter_name, char* parameter);
	json checkCorrectSpeed(std::string parameter_name, char* parameter);
	json checkCorrectLengthWave(std::string parameter_name, char* parameter);

	json checkCorrectState(std::string parameter_name, char* parameter);
	json checkCorrectModeName(std::string parameter_name, char* parameter);

	json setSettingsParameter(std::string parameter_name, char* parameter);
}