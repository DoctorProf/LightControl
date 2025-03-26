#include "../../include/validators/ValidatorApi.h"

bool validator_api::isMissingParameter(char* parameter)
{
	return parameter;
}
bool validator_api::isContainsParameter(std::string parameter_name, json object)
{
	for (auto it = object.begin(); it != object.end(); ++it)
	{
		if (parameter_name == it.key())
		{
			return true;
		}
	}
	return false;
}
int validator_api::isInvalidParameterInt(char* parameter)
{
	try
	{
		return std::stoi(parameter);
	}
	catch (const std::exception&)
	{
		return -1;
	}
}
float validator_api::isInvalidParameterFloat(char* parameter)
{
	try
	{
		return std::stof(parameter);
	}
	catch (const std::exception&)
	{
		return -1;
	}
}
bool validator_api::checkRange(int parameter, int min, int max)
{
	return !(parameter < min || parameter > max);
}
bool validator_api::checkRange(float parameter, float min, float max)
{
	return !(parameter < min || parameter > max);
}

json validator_api::checkCorrectBrightness(std::string parameter_name, char* parameter)
{
	json response;
	int value = isInvalidParameterInt(parameter);

	if (value != -1 && checkRange(value, 0, 255))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value);
		ConfigController::getInstance()->updateSettings(parameter_name, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json validator_api::checkCorrectSpeed(std::string parameter_name, char* parameter)
{
	json response;
	float value = isInvalidParameterFloat(parameter);

	if (value != -1 && checkRange(value, 0.f, 1.f))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value);
		ConfigController::getInstance()->updateSettings(parameter_name, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json validator_api::checkCorrectLengthWave(std::string parameter_name, char* parameter)
{
	json response;
	float value = isInvalidParameterFloat(parameter);

	if (value != -1 && checkRange(value, 0.f, 1.f))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value);
		ConfigController::getInstance()->updateSettings(parameter_name, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json validator_api::checkCorrectState(std::string parameter_name, char* parameter)
{
	json response;
	int value = isInvalidParameterInt(parameter);

	if (value != -1 && checkRange(value, 0, 1))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value);
		ConfigController::getInstance()->updateSettings(parameter_name, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json  validator_api::checkCorrectModeName(std::string parameter_name, char* parameter)
{
	json response;
	std::vector<std::string> modes = ConfigController::getInstance()->getModesNames();
	if (std::find(modes.begin(), modes.end(), parameter) == modes.end())
	{
		response["status"] = "Error";
		response["description"] = "Mode does not exist";
		return response;
	}
	response["status"] = "Success";
	response["description"] = std::format("{} set to {}", parameter_name, parameter);
	ConfigController::getInstance()->updateSettings(parameter_name, parameter);
	return response;
}
json validator_api::setSettingsParameter(std::string parameter_name, char* parameter)
{
	json response;

	if (!isContainsParameter(parameter_name, ConfigController::getInstance()->getSettings()))
	{
		response["status"] = "Error";
		response["description"] = "Parameter does not exist";
		return response;
	}
	if (!isMissingParameter(parameter))
	{
		response["status"] = "Error";
		response["description"] = "Missing parameter";
		return response;
	}
	if (parameter_name == "brightness")
	{
		return checkCorrectBrightness(parameter_name, parameter);
	}
	if (parameter_name == "speed")
	{
		return checkCorrectSpeed(parameter_name, parameter);
	}
	if (parameter_name == "length_wave")
	{
		return checkCorrectLengthWave(parameter_name, parameter);
	}
	if (parameter_name == "state")
	{
		return checkCorrectState(parameter_name, parameter);
	}
	if (parameter_name == "mode_name")
	{
		return checkCorrectModeName(parameter_name, parameter);
	}
}