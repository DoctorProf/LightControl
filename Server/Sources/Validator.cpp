#include "../Headers/Validator.h"

bool validator::missingParameter(char* parameter) 
{
	return parameter;
}
int validator::invalidParameter(char* parameter) 
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
    for (int i = 0; i < parameters.size(); ++i) 
    {
        if (!object.contains(parameters[i])) return false;
    }
    return true;
}
json validator::setParameter(char* parameter, std::string parameter_name, int min, int max)
{
    json response;
    int value = invalidParameter(parameter);
    if (value != -1 && checkRange(value, min, max)) 
    {
        response["ok"] = true;
        ConfigController::updateSettings(value, parameter_name);
        response["description"] = std::format("%s set to %d", parameter_name, value);
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