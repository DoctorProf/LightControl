#include "../Headers/Validator.h"

bool validator::isMissingParameter(char* parameter)
{
	return parameter;
}
bool validator::isContainsParameter(std::string parameter_name, json object)
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
int validator::isInvalidParameter(char* parameter)
{
	int value;

	value = std::atoi(parameter);
	try
	{
		value = std::stoi(parameter);
	}
	catch (const std::invalid_argument&)
	{
		return -1;
	}
	catch (const std::out_of_range&)
	{
		return -1;
	}
	return value;
}
bool validator::checkRange(int parameter, int min, int max)
{
	return !(parameter < min || parameter > max);
}
bool validator::checkBodyEmpty(crow::request req)
{
	return req.body.empty();
}
bool validator::checkCorrectParseJson(std::string str)
{
	try
	{
		json::parse(str);
		return true;
	}
	catch (const json::parse_error& e)
	{
		return false;
	}
}
bool validator::checkCorrectParameters(json object, std::vector<std::string> parameters)
{
	for (auto key : parameters)
	{
		if (!object.contains(key)) return false;
	}
	return true;
}
json validator::setSettingsParameter(std::string parameter_name, char* parameter)
{
	json response;
	if (!isMissingParameter(parameter))
	{
		response["status"] = "Error";
		response["description"] = "Missing parameter";
		return response;
	}
	if (!isContainsParameter(parameter_name, ConfigController::getSettings()))
	{
		response["status"] = "Error";
		response["description"] = "Parameter does not exist";
		return response;
	}
	int value = isInvalidParameter(parameter);
	std::vector<int> range;
	if (parameter_name == "brightness")
	{
		range = { 0, 255 };
	}
	else if (parameter_name == "state")
	{
		range = { 0, 1 };
	}
	else if (parameter_name == "mode_id")
	{
		range = { 0, ConfigController::getCountModes() - 1 };
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter name";
		return response;
	}
	if (value != -1 && checkRange(value, range[0], range[1]))
	{
		response["status"] = "Success";
		response["description"] = std::format("{} set to {}", parameter_name, value);
		ConfigController::updateSettings(parameter_name, value);
		return response;
	}
	else
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameter";
		return response;
	}
}
json validator::setModeParameter(std::string parameter_name, char* parameter)
{
	json response;
	if (!isMissingParameter(parameter))
	{
		response["status"] = "Error";
		response["description"] = "Missing parameter";
		return response;
	}
	if (!isContainsParameter(parameter_name, ConfigController::getCurrentModeOptions()))
	{
		response["status"] = "Error";
		response["description"] = "Parameter does not exist";
		return response;
	}
	ConfigController::updateModeOptions(parameter_name, parameter);
	response["status"] = "Success";
	response["description"] = std::format("{} set to {}", parameter_name, parameter);
	return response;
}
json validator::addMode(crow::request req)
{
	json response;
	if (checkBodyEmpty(req))
	{
		response["status"] = "Error";
		response["description"] = "Body is empty";
		return response;
	}
	if (!checkCorrectParseJson(req.body))
	{
		response["status"] = "Error";
		response["description"] = "Invalid JSON format";
		return response;
	}
	json mode = json::parse(req.body);
	if (!checkCorrectParameters(mode, { "options", "name", "static" }))
	{
		response["status"] = "Error";
		response["description"] = "Invalid parameters";
		return response;
	}

	response["status"] = "Success";
	response["description"] = "Mode added";
	response["mode_id"] = ConfigController::addMode(mode);
	return response;
}
json validator::deleteMode(crow::request req)
{
	json response;
	try
	{
		ConfigController::deleteMode();
		response["status"] = "Success";
		response["description"] = "Mode deleted";
		return response;
	}
	catch (const json::out_of_range&)
	{
		response["status"] = "Error";
		response["description"] = "No mods to remove";
		return response;
	}
}