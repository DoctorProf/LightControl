#include "../Headers/Validator.h"

bool validator::isMissingParameter(char* parameter) 
{
	return parameter;
}
bool validator::isContainsParameter(std::string parameter_name)
{
    std::cout << ConfigController::getSettings().dump();
    json settings = ConfigController::getSettings();
    for (auto it = settings.begin(); it != settings.end(); ++it)
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
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return response;
    }
    if (!isContainsParameter(parameter_name))
    {
        response["ok"] = false;
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
        range = { 0, (int)(ConfigController::getModes().size() - 1) };
    }
    else 
    {
        response["ok"] = false;
        response["description"] = "Invalid parameter name";
        return response;
    }
    if (value != -1 && checkRange(value, range[0], range[1]))
    {
        response["ok"] = true;
        ConfigController::updateSettings(value, parameter_name);
        response["description"] = std::format("{} set to {}", parameter_name, value);
        return response;
    }
    else 
    {
        response["ok"] = false;
        response["description"] = "Invalid parameter";
        return response;
    }
}
json validator::addMode(crow::request req)
{
    json response;
    if (checkBodyEmpty(req)) 
    {
        response["ok"] = false;
        response["description"] = "Body is empty";
        return response;
    }
    if (!checkCorrectParseJson(req.body)) 
    {
        response["ok"] = false;
        response["description"] = "Invalid JSON format";
        return response;
    }
    json mode = json::parse(req.body);
    if (!checkCorrectParameters(mode, {"options", "name", "static"}))
    {
        response["ok"] = false;
        response["description"] = "Invalid parameters";
        return response;
    }

    response["ok"] = true;
    response["description"] = "Mode added";
    response["mode_id"] = ConfigController::addMode(mode);
    return response;
}