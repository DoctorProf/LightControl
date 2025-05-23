#include "../../include/validators/ValidatorApi.h"

bool validator_api::isMissingParameter(char* value)
{
	return value;
}
bool validator_api::isContainsParameter(std::string param_name, json object)
{
	for (auto it = object.begin(); it != object.end(); ++it)
	{
		if (param_name == it.key())
		{
			return true;
		}
	}
	return false;
}
int validator_api::isInvalidParameterInt(char* value)
{
	try
	{
		return std::stoi(value);
	}
	catch (const std::exception&)
	{
		return -1;
	}
}
float validator_api::isInvalidParameterFloat(char* value)
{
	try
	{
		float float_value = std::round(std::stof(value) * 100.0f) / 100.0f;
		return float_value;
	}
	catch (const std::exception&)
	{
		return -1;
	}
}
bool validator_api::checkRange(int value, int min, int max)
{
	return !(value < min || value > max);
}
bool validator_api::checkRange(float value, float min, float max)
{
	return !(value < min || value > max);
}

bool validator_api::checkCorrectHex(std::string hex)
{
	static const std::regex hex6_regex("^#[0-9a-fA-F]{6}$");
	return std::regex_match(hex, hex6_regex);
}
json validator_api::checkCorrectBrightness(std::string parameter_name, char* value)
{
	json response;
	int value_int = isInvalidParameterInt(value);

	if (value_int != -1 && checkRange(value_int, 0, 255))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value_int);
		ConfigController::getInstance()->updateSettings(parameter_name, value_int);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json validator_api::checkCorrectState(std::string parameter_name, char* value)
{
	json response;
	int value_int = isInvalidParameterInt(value);

	if (value_int != -1 && checkRange(value_int, 0, 1))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value_int);
		ConfigController::getInstance()->updateSettings(parameter_name, value_int);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json  validator_api::checkCorrectModeName(std::string parameter_name, char* value)
{
	json response;
	std::vector<std::string> modes = ConfigController::getInstance()->getModesNames();
	if (std::find(modes.begin(), modes.end(), value) == modes.end())
	{
		response["status"] = "Error";
		response["description"] = "Mode does not exist";
		return response;
	}
	response["status"] = "Success";
	response["description"] = std::format("{} set to {}", parameter_name, value);
	ConfigController::getInstance()->updateSettings(parameter_name, value);
	return response;
}
json validator_api::setSettingsParameter(std::string parameter_name, char* value)
{
	json response;
	if (!isContainsParameter(parameter_name, ConfigController::getInstance()->getSettings()))
	{
		response["status"] = "Error";
		response["description"] = "Parameter does not exist";
		return response;
	}
	if (!isMissingParameter(value))
	{
		response["status"] = "Error";
		response["description"] = "Missing parameter";
		return response;
	}
	if (parameter_name == "brightness")
	{
		return checkCorrectBrightness(parameter_name, value);
	}
	if (parameter_name == "state")
	{
		return checkCorrectState(parameter_name, value);
	}
	if (parameter_name == "mode_name")
	{
		return checkCorrectModeName(parameter_name, value);
	}
}
json validator_api::setModeParameter(std::string parameter_name, std::string internal_param, char* parameter)
{
	json response;
	if (!isContainsParameter(parameter_name, ConfigController::getInstance()->getModeParams()) &&
		!isContainsParameter(internal_param, ConfigController::getInstance()->getModeParams()[parameter_name]))
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
	if (ConfigController::getInstance()->getModeParams()[parameter_name]["type"].get<std::string>() == "color")
	{
		if (!checkCorrectHex(parameter))
		{
			response["status"] = "Error";
			response["description"] = "Invalid hex value";
			return response;
		}
		response["status"] = "Success";
		response["description"] = std::format("{}, {} set to {}", parameter_name, internal_param, parameter);
		ConfigController::getInstance()->updateParamsMode(parameter_name, internal_param, parameter);
		return response;
	}
	float value = isInvalidParameterFloat(parameter);
	auto data = ConfigController::getInstance()->getModeParams()[parameter_name];
	float min = data.value("min", 0.0);
	float max = data.value("max", 0.0);
	if (value != -1 && checkRange(value, min, max))
	{
		response["status"] = "Success";
		response["description"] = std::format("{}, {} set to {}", parameter_name, internal_param, parameter);
		ConfigController::getInstance()->updateParamsMode(parameter_name, internal_param, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}