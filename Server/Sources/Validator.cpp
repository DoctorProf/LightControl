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
bool validator::checkCorrectParseJson(crow::request req)
{
    try
    {
        json mode = json::parse(req.body);
        return true;
    }
    catch (const json::parse_error& e)
    {
        return false;
    }
}
bool validator::checkCorrectParameters(json mode, std::vector<std::string> parameters)
{
    for (int i = 0; i < parameters.size(); ++i) 
    {
        if (!mode.contains(parameters[i])) return false;
    }
    return true;
}
json validator::setParameter(char* parameter, std::string name_parameter, int min, int max)
{
    json response;
    int value = invalidParameter(parameter);
    if (value != -1 && checkRange(value, min, max)) 
    {
        json config_json;
        std::ifstream input_file("config.json");
        input_file >> config_json;
        input_file.close();
        config_json["info"][name_parameter] = value;

        std::ofstream output_file("config.json");
        output_file << config_json.dump(4);

        response["ok"] = true;
        response["description"] = "Parameter set to " + std::to_string(value);
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
    if (!checkCorrectParseJson(req)) 
    {
        response["ok"] = false;
        response["description"] = "Invalid JSON format";
        return response;
    }
    json mode = json::parse(req.body);
    if (!checkCorrectParameters(mode, {"static", "name" })) 
    {
        response["ok"] = false;
        response["description"] = "Invalid parameters";
        return response;
    }
    json config_json;
    std::ifstream input_file("config.json");
    input_file >> config_json;
    input_file.close();

    mode["id"] = config_json["modes"].size();

    config_json["modes"].push_back(mode);

    std::ofstream output_file("config.json");
    output_file << config_json.dump(4);

    response["ok"] = true;
    response["description"] = "Mode added";
    response["mode_id"] = mode["id"];
    return response;
}